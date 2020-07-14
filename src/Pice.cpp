//
// Created by Rato Zumbi on 03/07/2020.
//

#include <iostream>
#include "../include/Game.h"
#include "../include/Pice.h"

Pice::Pice():Actor() {

};

Pice::~Pice() {
    Game::scenes.at(Util::findScene("game")).deleteImage(piceImg);
};

Pice::Pice(PiceType type): Actor() {
    type = type;
    piceImg = Game::scenes.at(Util::findScene("game")).loadImage(colors[(int)type]);
};

void Pice::start() {
};

int Pice::update() {
    Actor::update();

    //enlarge for click
    if(clicked){
        piceImg->rect.h = PICE_DIMENSION + 10;
        piceImg->rect.w = PICE_DIMENSION + 10;
    } else{
        piceImg->rect.h = PICE_DIMENSION;
        piceImg->rect.w = PICE_DIMENSION;
    }

    if(isMoving ==true){
        if(!pointsToMove.empty()){
            int lerpX =std::ceil(Util::lerp(piceImg->rect.x,pointsToMove.at(0).x,0.1f));
            int lerpY =std::ceil(Util::lerp(piceImg->rect.y,pointsToMove.at(0).y,0.1f));
            //unstuck broken float to int conversion
            if(lerpX == piceImg->rect.x && lerpY == piceImg->rect.y){
                piceImg->rect.x = pointsToMove.at(0).x;
                piceImg->rect.y = pointsToMove.at(0).y;
            } else{
                piceImg->rect.x = lerpX;
                piceImg->rect.y = lerpY;
            }

            if(piceImg->rect.x == pointsToMove.at(0).x && piceImg->rect.y == pointsToMove.at(0).y )
            {
                pointsToMove.erase(pointsToMove.begin());
            }
        } else{
            isMoving = false;
        }

    } else if(!pointsToMove.empty()){
        isMoving =true;
    }

    //spin
    if(isMoving != true && isSpining == 1){
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
    isMoving = true;
    pointsToMove.push_back({x,y});
}

void Pice::moveDown(int squares) {
    moveTo(piceImg->rect.x,piceImg->rect.y + piceImg->rect.h * squares);
}

void Pice::spin(){
    isSpining = 1;
}

bool Pice::isAnimating() {
    return isMoving == true || isSpining ==1;
}