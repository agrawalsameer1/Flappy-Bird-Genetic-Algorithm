#include "../include/SDL2/SDL.h"
#include <random>

#pragma once

class Obstacle {
    public:
        int w = 20;

        int topBarH;
        int bottomBarH;

        SDL_Rect topBar;
        SDL_Rect bottomBar;
        SDL_Rect scoreRect;

        Obstacle();
        Obstacle(int windowW, int windowH);

        bool checkBounds();
        void updatePos(double dt, double speed);
        void render(SDL_Renderer* renderer);

        int generateRandomInt(int min, int max) {
            // Create a random device and a random number generator
            std::random_device rd;
            std::mt19937 gen(rd());

            // Define the range
            std::uniform_int_distribution<> dis(min, max);

            // Generate and return the random integer
            return dis(gen);
        }
};