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
    if(movedownCount !=0 && isMoving != 1){
        moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h);
    }
    if(isMoving == 1){
        int speedX = 1;
        int speedY = 1;
        speedX = targetX < piceImg->rect.x ? speedX * -1: targetX == piceImg->rect.x? 0:speedX;
        speedY = targetY < piceImg->rect.y ? speedY * -1: targetY == piceImg->rect.y? 0:speedY;
        piceImg->rect.x += speedX;
        piceImg->rect.y += speedY;

        if(piceImg->rect.x == targetX && piceImg->rect.y == targetY )
        {
            movedownCount--;
            if(movedownCount != 0){
                moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h);
            } else{
                targetX = 0;
                targetY = 0;
                isMoving = 2;
            }
        }
    }
    if(isMoving != 1 && isSpining == 1){
        piceImg->angle+=2;
        if(piceImg->angle > 180){
            isSpining = 2;
        }
    }

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
    spin();
}

bool Pice::getDestroy() {
    return Actor::getDestroy();
}
void Pice::moveTo(int x, int y) {
    isMoving = 1;
    targetX = x;
    targetY = y;
}

void Pice::moveDown(int squares) {
    if(movedownCount == 0)moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h);
    movedownCount += squares;

//    moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h);
//    piceImg->rect.y = piceImg->rect.y + piceImg->rect.h;
}

void Pice::spin(){
    isSpining = 1;
//    piceImg->rect.
}

bool Pice::isAnimating() {
    return isMoving == 1 || isSpining ==1;
}