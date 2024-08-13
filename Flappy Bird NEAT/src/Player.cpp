#include "Player.h"

Player::Player() {
    ;
}

Player::Player(double xCoord, double yCoord, double yVelocity, double width, int brainDims) {
    x = xCoord;
    y = yCoord;

    yVel = yVelocity;

    w = width;

    brain = Model(brainDims);

    player_rect = SDL_Rect();

    player_rect.x = x;
    player_rect.y = y;

    player_rect.w = w;
    player_rect.h = w;

    alive = true;

    int whichToBeBright = createRandomInt(1, 3);

    if (whichToBeBright == 1) {
        R = createRandomInt(180, 255);
        G = createRandomInt(0, 255);
        B = createRandomInt(0, 255);
    }

    else if (whichToBeBright == 2) {
        G = createRandomInt(180, 255);
        R = createRandomInt(0, 255);
        B = createRandomInt(0, 255);
    }

    else {
        B = createRandomInt(180, 255);
        G = createRandomInt(0, 255);
        R = createRandomInt(0, 255);
    }
}

void Player::set(Player p) {
    x = p.x;
    y = p.y;

    yVel = p.yVel;

    w = p.w;

    brain = Model(p.brain.getDims());

    brain.params.set(p.brain.getParams());

    player_rect.x = x;
    player_rect.y = y;

    player_rect.w = w;
    player_rect.h = w;

    R = p.R;
    G = p.G;
    B = p.B;

    alive = true;
}

bool Player::evalJump(int windowH, double topPoleDist, double bottomPoleDist) {
    Matrix inputs = Matrix(4);

    for (int i = 0; i < 4; i++) {
        if (i == 0) {
            inputs.set(i, y/windowH);
        }
        
        if (i == 1) {
            inputs.set(i, (windowH-y)/windowH);
        }

        if (i == 2) {
            inputs.set(i, topPoleDist);
        }

        if (i == 3) {
            inputs.set(i, bottomPoleDist);
        }
    }

    return brain.params.multiply(inputs) > 0;

    delete[] inputs.vals;
}

void Player::flap(double flapStrength) {
    if (alive) {
        yVel = flapStrength;
    }
}

void Player::updatePos(double dt, double gravity) {
    if (alive) {
        yVel += gravity*dt;
        y += yVel;

        player_rect.y = y;
    }
}

bool Player::isIntersecting(SDL_Rect rect) {
    if (alive) {
        double smallerX = x <= rect.x ? x : rect.x;
        double largerX = x == smallerX ? rect.x : x;
        double smallerY = y <= rect.y ? y : rect.y;
        double largerY = y == smallerY ? rect.y : y;

        double smallerXR = x == smallerX ? x + w : rect.x + rect.w;

        double largerXL = x == largerX ? x : rect.x;
        
        double smallerYB = y == smallerY ? y + w : rect.y + rect.h;

        double largerYT = y == largerY ? y  : rect.y;

        return smallerXR >= largerXL && smallerYB >= largerYT;
    }
    else {
        return false;
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (alive) {
        SDL_SetRenderDrawColor(renderer, R, G, B, 255);
        SDL_RenderFillRect(renderer, &player_rect);
    }
}