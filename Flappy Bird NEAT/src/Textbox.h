#include "../include/SDL2/SDL.h"
#include "../include/SDL2_ttf/SDL_ttf.h"
#include <iostream>
#include <cstdlib>

#pragma once

class Textbox {
    public:
        SDL_Rect box;

        std::string label;
        int value;

        TTF_Font *font;
        int fontSize;

        SDL_Color textColor;

        Textbox();
        Textbox(std::string labelInput, int size, int x, int y, int w, int h, int defaultValue = 0, std::string fontPath = "/Users/sameeragrawal/Flappy Bird NEAT/src/font.ttf");

        void updateValue(int updatedValue);
        void incValue(bool decrease = false);

        void render(SDL_Renderer* renderer, SDL_Window *window);
};