#include "Obstacle.h"

#define OBSTACLE_DIST 0.1

Obstacle::Obstacle() {
    ;
}

Obstacle::Obstacle(int windowW, int windowH) {
    w = 20;

    topBarH = generateRandomInt(0.1*windowH, windowH*(1-OBSTACLE_DIST - 0.1));
    bottomBarH = windowH - topBarH - OBSTACLE_DIST*windowH;

    topBar.x = windowW * 1.3;
    bottomBar.x = windowW * 1.3;

    topBar.y = 0;
    bottomBar.y = topBarH + OBSTACLE_DIST*windowH;

    topBar.w = 20;
    bottomBar.w = 20;

    topBar.h = topBarH;
    bottomBar.h = bottomBarH;

    scoreRect.x = bottomBar.x + bottomBar.w;
    scoreRect.y = topBar.h;
    scoreRect.w = 20;
    scoreRect.h = OBSTACLE_DIST*windowH;
}

void Obstacle::updatePos(double dt, double speed) {
    topBar.x -= speed*dt;
    bottomBar.x -= speed*dt;
    scoreRect.x -= speed*dt;
}

bool Obstacle::checkBounds() {
    return topBar.x <= 5 && bottomBar.x <= 5;
}

void Obstacle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 160, 0, 255);
    SDL_RenderFillRect(renderer, &topBar);
    SDL_RenderFillRect(renderer, &bottomBar);
}