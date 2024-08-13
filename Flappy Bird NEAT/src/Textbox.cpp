#include "Textbox.h"

Textbox::Textbox() {
    TTF_Init();
    std::string fontPath = "/Users/sameeragrawal/Flappy Bird NEAT/src/font.ttf";
    font = TTF_OpenFont(fontPath.c_str(), 24);
    fontSize = 24;
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
}

Textbox::Textbox(std::string labelInput, int size, int x, int y, int w, int h, int defaultValue, std::string fontPath) {
    TTF_Init();

    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    label = labelInput;
    value = defaultValue;

    fontSize = size;
    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    textColor.a = 255;
}

void Textbox::updateValue(int updatedValue) {
    value = updatedValue;
}

void Textbox::incValue(bool decrease) {
    if (decrease) {
        value -= 1;
    }

    else {
        value += 1;
    }
}

void Textbox::render(SDL_Renderer* renderer, SDL_Window *window) {
    std::string valString = std::to_string(value);
    std::string separator = ": ";

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, (label + separator + valString).c_str(), textColor);
    box.w = surfaceMessage->w;
    box.h = surfaceMessage->h;
    
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    box.w = surfaceMessage->w;
    box.h = surfaceMessage->h;
    SDL_RenderCopy(renderer, Message, NULL, &box);
}