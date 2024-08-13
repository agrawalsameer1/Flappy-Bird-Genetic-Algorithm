#include "Model.h"
#include "../include/SDL2/SDL.h"

#pragma once

class Player {
    public:
        Model brain;

        double x;
        double y;

        double yVel;

        double w;

        bool alive = true;

        SDL_Rect player_rect;

        int R = 0;
        int G = 0;
        int B = 0;

        Player();
        Player(double xCoord, double yCoord, double yVelocity = 0, double width = 10, int brainDims = 1);

        void set(Player p);
        
        bool evalJump(int windowH, double topPoleDist, double bottomPoleDist);
        void flap(double flapStrength);
        void updatePos(double dt, double gravity);

        bool isIntersecting(SDL_Rect rect);

        void render(SDL_Renderer* renderer);

        int createRandomInt(int min, int max) {
            // Create a random device and a random number generator
            std::random_device rd;
            std::mt19937 gen(rd());

            // Define the range
            std::uniform_int_distribution<> dis(min, max);

            // Generate and return the random integer
            return dis(gen);
        }
};