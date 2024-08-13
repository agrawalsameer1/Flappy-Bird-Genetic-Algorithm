#include "Player.h"
#include "Obstacle.h"
#include "Population.h"
#include "Textbox.h"

#include <vector>

#pragma once

class Game {
    public:
        Player* players;
        Population playerPop;
        int nPlayers;
        int nDeadPlayers;

        std::vector<Obstacle> obstacles;

        int windowH;
        int windowW;

        SDL_Rect ground;

        Textbox currentGeneration;
        Textbox currentScore;
        Textbox numPlayersLeft;

        Game(SDL_Window* window);
        Game(int windowHeight, int windowWidth);

        ~Game();

        void initPlayers(double xPos, double yPos, int brainDims, int n, double yVel = 0, double width = 10);
        void addObstacle();

        int checkPlayerCollision(Obstacle nearest);

        void setAllLivingFitnesses();

        void deleteObstacles();

        int update(double dt, double gravity, double speed);

        void reset();

        void render(SDL_Renderer* renderer, SDL_Window* window);
};