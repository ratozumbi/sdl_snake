//
// Created by Rato Zumbi on 03/07/2020.
//

#include <iostream>
#include "../include/Game.h"
#include "../include/Pice.h"

const char * Pice::getRandomColor(){
    return colors[rand() % 5];
}

Pice::Pice():Actor() {

};

Pice::~Pice() {
    Game::scenes.at(1).deleteImage(piceImg);
};

Pice::Pice(PiceType type): Actor() {
    type = type;
    piceImg = Game::scenes.at(Util::findScene("game")).loadImage(colors[(int)type]);
};

void Pice::start() {
};

int Pice::update(){
    Actor::update();
    return 0;
};

int Pice::onInput(SDL_Event e){
    Actor::onInput(e);
    bool insideBounds = (e.button.x >= piceImg->rect.x &&
                         e.button.x <= piceImg->rect.x + piceImg->rect.w &&
                         e.button.y >= piceImg->rect.y &&
                         e.button.y <= piceImg->rect.y + piceImg->rect.h);

    if(insideBounds && e.type == SDL_MOUSEBUTTONUP){
        if(e.button.button == SDL_BUTTON_RIGHT){
            setDestroy();
        }
    }

    if(insideBounds && e.type == SDL_MOUSEMOTION){
        if(e.motion.state == SDL_BUTTON_LMASK){
            piceImg->rect.x += e.motion.xrel;
            piceImg->rect.y += e.motion.yrel;
        }
    }
    return 0;
}

void Pice::setDestroy() {
    Actor::setDestroy();
}

bool Pice::getDestroy() {
    return Actor::getDestroy();
}

void Pice::moveDown() {
    piceImg->rect.y = piceImg->rect.y + piceImg->rect.h;
}
