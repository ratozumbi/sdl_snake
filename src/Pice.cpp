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
    if(movedownCount !=0 && isMoving == false){
        moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h);
    }
    if(isMoving){

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
                isMoving = false;
                if(markToDestroy) active = false;
            }

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
            std::cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>> DELTE DEBUG MESSAGE Pice" << std::endl;
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
void Pice::moveTo(int x, int y) {
    isMoving = true;
    targetX = x;
    targetY = y;
}

void Pice::moveDown() {
    movedownCount ++;
//    moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h);
//    piceImg->rect.y = piceImg->rect.y + piceImg->rect.h;
}

void Pice::spin(){
//    piceImg->rect.
}