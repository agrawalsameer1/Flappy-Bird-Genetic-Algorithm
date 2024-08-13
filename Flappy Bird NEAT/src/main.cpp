#include "Population.h"
#include "Game.h"

#include <vector>

// Window size
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define FRAME_RATE 100

int generateRandomInteger(int min, int max) {
    // Create a random device and a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range
    std::uniform_int_distribution<> dis(min, max);

    // Generate and return the random integer
    return dis(gen);
}
    
int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT + 120, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    int nPlayers = 50;
    int nParents = 5;
    int nKeepSame = 1;
    int iterCount = 200;

    bool keyDown = false;

    Game game = Game(WINDOW_HEIGHT, WINDOW_WIDTH);
    game.initPlayers(150, 150, 4, nPlayers); // 4

    bool hardQuit = false;

    for (int iters = 0; iters < iterCount; iters++) {
        if (hardQuit) {
            break;
        }

        int run = 0;
        int frameCtr = 0;

        game.reset();

        while (run != -1) {
            Uint64 start = SDL_GetPerformanceCounter();

            SDL_Event e;

            if (frameCtr % 350 == 0) {
                game.addObstacle();
            }
            
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    hardQuit = true;
                }

                else if (e.type==SDL_KEYDOWN && !keyDown) {
                    keyDown = true;

                    if (e.key.keysym.sym == SDLK_n) {
                        game.setAllLivingFitnesses();
                        run = -1;
                    }
                }

                else if (e.type==SDL_KEYUP) {
                    keyDown = false;
                }
            }

            if (hardQuit || run == -1) {
                break;
            }

            run = game.update(1./FRAME_RATE, 1.5, 1.5);

            game.render(ren, win);

            SDL_SetRenderDrawColor(ren, 135, 206, 250, 100);

            SDL_RenderPresent(ren); 
            SDL_UpdateWindowSurface(win);

            Uint64 end = SDL_GetPerformanceCounter();
            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

            SDL_Delay(floor(1000./FRAME_RATE - elapsedMS));
            SDL_RenderClear(ren);

            frameCtr++;
        }

        if (hardQuit) {
            break;
        }

        Population fittest = game.playerPop.getFittest(nParents);       
        Population crossedOver = fittest.crossOver(nPlayers, nKeepSame, 0.2);

        game.playerPop.setPopulation(crossedOver);

        for (int i = 0; i < nPlayers; i++) {
            game.players[i].brain.setParams(game.playerPop.population[i].getParams());
        }

        SDL_Delay(1000);

        if (iters == iterCount-1) {
            std::cout << "Best params: " << fittest.population[0].getParams() << "\n";
        }
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
}