#include "Game.h"

Game::Game(SDL_Window* window) {
    SDL_GetWindowSize(window, &windowW, &windowH);
}

Game::Game(int windowHeight, int windowWidth) {
    windowH = windowHeight;
    windowW = windowWidth;

    ground.w = windowW;
    ground.h = 120;

    ground.x = 0;
    ground.y = windowH;

    currentGeneration = Textbox("Generation", 18, 3*windowW/4, windowHeight + 20, windowW/3, 20);
    currentScore = Textbox("Score", 18, 3*windowW/4, windowHeight + 50, windowW/3, 20);
    numPlayersLeft = Textbox("Players Alive", 18, 3*windowW/4, windowHeight + 80, windowW/3, 20);
}

Game::~Game() {
    delete[] players;
    obstacles.clear();
}

void Game::initPlayers(double xPos, double yPos, int brainDims, int n, double yVel, double width) {
    nPlayers = n;
    nDeadPlayers = 0;

    numPlayersLeft.updateValue(nPlayers);

    players = new Player[nPlayers];
    playerPop = Population(brainDims, nPlayers);

    for (int i = 0; i < nPlayers; i++) {
        players[i].set(Player(xPos, yPos, yVel, width, brainDims));
        playerPop.population[i].setParams(players[i].brain.params);
    }
}

void Game::addObstacle() {
    obstacles.push_back(Obstacle(windowW, windowH));
}

int Game::checkPlayerCollision(Obstacle nearest) {
    bool scoreUpdated = false;

    for (int i = 0; i < nPlayers; i++) {
        if ((players[i].y < -10 || players[i].y > windowH - 10) && players[i].alive) {
            players[i].alive = false;
            nDeadPlayers++;
            playerPop.population[i].setFitness(players[i].brain.fitness);
            numPlayersLeft.incValue(true);

            continue;
        }

        for (int j = 0; j < obstacles.size(); j++) {
            if ((players[i].isIntersecting(obstacles[j].topBar) || players[i].isIntersecting(obstacles[j].bottomBar)) && players[i].alive) {
                players[i].alive = false;
                nDeadPlayers++;
                
                double midPipe = (nearest.topBarH + nearest.bottomBar.y)/2.;
                double midPlayer = (players[i].y) + players[i].w/2.;
                playerPop.population[i].setFitness(players[i].brain.fitness + (windowH - abs(midPlayer - midPipe)));
                numPlayersLeft.incValue(true);

                break;
            }
        }

        if (players[i].alive) {
            for (int j = 0; j < obstacles.size(); j++) {
                if (!scoreUpdated) {
                    if (players[i].x + players[i].w == obstacles[j].scoreRect.x) {
                        currentScore.incValue();
                        scoreUpdated = true;
                        break;
                    }
                }
            }
        }
    }

    if (nDeadPlayers == nPlayers) {
        return -1;
    }

    else {
        return 0;
    }
}

void Game::setAllLivingFitnesses() {
    for (int i = 0; i < nPlayers; i++) {
        if (players[i].alive) {
            playerPop.population[i].setFitness(players[i].brain.getFitness());
        }
    }
}

void Game::deleteObstacles() {
    int i = 0;

    while (i < obstacles.size()) {
        if (obstacles[i].checkBounds()) {
            obstacles.erase(obstacles.begin() + i);
        }

        else {
            i++;
        }
    }
}

int Game::update(double dt, double gravity, double speed) {
    deleteObstacles();

    Obstacle nearest;

    for (int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].topBar.x + obstacles[i].topBar.w >= players[0].x) {
            nearest = obstacles[i];
            break;
        }
    }

    int allDead = checkPlayerCollision(nearest);

    if (allDead == -1) {
        return -1;
    }

    for (int i = 0; i < nPlayers; i++) {
        double distToTopBar = (nearest.topBar.y + nearest.topBar.h - players[i].y)/windowH;
        double distToBottomBar = (nearest.bottomBar.y - (players[i].y + players[i].w))/windowH;

        if (players[i].evalJump(windowH, distToTopBar, distToBottomBar)) {
            players[i].flap(-1);
        }

        players[i].updatePos(dt, gravity);

        players[i].brain.fitness += 1;
    }

    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i].updatePos(dt, speed);
    }

    return 0;
}

void Game::reset() {
    while (obstacles.size() > 0) {
        obstacles.erase(obstacles.begin());
    }

    nDeadPlayers = 0;

    for (int i = 0; i < nPlayers; i++) {
        players[i].alive = true;

        players[i].x = 150;
        players[i].y = 150;
        players[i].yVel = 0;

        players[i].player_rect.x = players[i].x;
        players[i].player_rect.y = players[i].y;

        players[i].brain.setFitness(0);
        playerPop.population[i].setFitness(0);
    }

    currentGeneration.incValue();
    currentScore.updateValue(0);
    numPlayersLeft.updateValue(nPlayers);
}

void Game::render(SDL_Renderer* renderer, SDL_Window* window) {
    for (int i = 0; i < nPlayers; i++) {
        players[i].render(renderer);
    }

    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i].render(renderer);
    }

    SDL_SetRenderDrawColor(renderer, 0, 160, 0, 255);
    SDL_RenderFillRect(renderer, &ground);

    currentGeneration.render(renderer, window);
    currentScore.render(renderer, window);
    numPlayersLeft.render(renderer, window);
}