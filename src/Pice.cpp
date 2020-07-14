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

int Pice::update() {
    Actor::update();

    if(isMoving ==1){
        if(!pointsToMove.empty()){
            int lerpX =std::ceil(Util::lerp(piceImg->rect.x,pointsToMove.at(0).x,0.1f));
            int lerpY =std::ceil(Util::lerp(piceImg->rect.y,pointsToMove.at(0).y,0.1f));
            //unstuck broken float to int conversion
            if(lerpX == piceImg->rect.x && lerpY == piceImg->rect.y){
                piceImg->rect.x = pointsToMove.at(0).x;
                piceImg->rect.y = pointsToMove.at(0).y;
            } else{
                piceImg->rect.x = lerpX;//std::ceil(Util::lerp(piceImg->rect.x,pointsToMove.at(0).x,1.0f));
                piceImg->rect.y = lerpY;//std::ceil(Util::lerp(piceImg->rect.y,pointsToMove.at(0).y,1.0f));
            }

            if(piceImg->rect.x == pointsToMove.at(0).x && piceImg->rect.y == pointsToMove.at(0).y )
            {
                pointsToMove.erase(pointsToMove.begin());
//                if(pointsToMove.empty()) isMoving =0;
            }
        } else{
            isMoving = 0;
        }

    } else if(!pointsToMove.empty()){
        isMoving =1;
    }

    //spin
    if(isMoving != 1 && isSpining == 1){
        piceImg->angle+=2;
        if(piceImg->angle > 180){
            isSpining = 2;
        }
    }

    return 0;
}

int Pice::onInput(SDL_Event e){
    Actor::onInput(e);
    bool insideBounds = (e.button.x >= piceImg->rect.x &&
                         e.button.x <= piceImg->rect.x + piceImg->rect.w &&
                         e.button.y >= piceImg->rect.y &&
                         e.button.y <= piceImg->rect.y + piceImg->rect.h);

    if(insideBounds && e.type == SDL_MOUSEBUTTONDOWN){
        if(e.button.button == SDL_BUTTON_RIGHT){
            setDestroy();
        }
        if(e.button.button == SDL_BUTTON_LEFT){
            clicked =true;
        }
    }

//    if(insideBounds && e.type == SDL_MOUSEMOTION){
//        if(e.motion.state == SDL_BUTTON_LMASK){
//            clicked = true;
////            piceImg->rect.x += e.motion.xrel;
////            piceImg->rect.y += e.motion.yrel;
//        }
//    }
    return 0;
}

void Pice::setDestroy() {
    Actor::setDestroy();
    spin();
}

bool Pice::getDestroy() {
    return Actor::getDestroy();
}

//TODO: swap x y
void Pice::moveTo(int x, int y) {
    isMoving = 1;
    pointsToMove.push_back({x,y});
    targetX = x;
    targetY = y;
}

void Pice::moveDown(int squares) {
    moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h * squares);
//    if(movedownCount == 0)moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h);
//    movedownCount += squares;

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