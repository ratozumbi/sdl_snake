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
//    if(clicked){
//        piceImg->rect.x = PICE_DIMENSION - 5;
//        piceImg->rect.y = PICE_DIMENSION - 5;
//        piceImg->rect.h = PICE_DIMENSION + 10;
//        piceImg->rect.w = PICE_DIMENSION + 10;
//    } else{
//        piceImg->rect.h = PICE_DIMENSION;
//        piceImg->rect.w = PICE_DIMENSION;
//    }

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
        if(e.button.button == SDL_BUTTON_LEFT){
            setClicked(true);
            //set Z to front most
            Game::scenes.at(1).setZindex(piceImg,SDL_MAX_SINT16);
        }
        if(e.button.button == SDL_BUTTON_RIGHT && drag == false && isMoving == false){
            setClicked(true);
            drag = true;
            //set Z to front most
            Game::scenes.at(1).setZindex(piceImg,SDL_MAX_SINT16);
        }
    }

    //move the pice
    if(e.type == SDL_MOUSEMOTION){
        if(drag){
            piceImg->rect.x = e.motion.x - PICE_DIMENSION/2;
            piceImg->rect.y = e.motion.y- PICE_DIMENSION/2;
        }
    }

    if(e.type == SDL_MOUSEBUTTONUP){
        if(e.button.button == SDL_BUTTON_RIGHT && drag == true){
            drag =false;
            //notify drag drop

            SDL_Event event;
            SDL_zero(event);//SDL_memset(&event, 0, sizeof(event));
            event.type = Engine::dragEventType;
            event.user.code = 0;
            event.user.data1 = new SDL_Point {e.motion.x,e.motion.y};
            event.user.data2 = this;
            SDL_PushEvent(&event);
        }
    }
    //listen to drop
    if(e.type == SDL_USEREVENT){
        if(e.user.type == Engine::dragEventType){
            if(
                    ((SDL_Point*)e.user.data1)->x >= piceImg->rect.x &&
                    ((SDL_Point*)e.user.data1)->x <= piceImg->rect.x + piceImg->rect.w &&
                    ((SDL_Point*)e.user.data1)->y >= piceImg->rect.y &&
                    ((SDL_Point*)e.user.data1)->y <= piceImg->rect.y + piceImg->rect.h
                    &&
                    ((Pice*)e.user.data2) != this)
            {
                setClicked(true);
            }
        }
    }

    if(insideBounds && e.type == SDL_MOUSEMOTION){
        if(e.motion.type == SDL_MOUSEMOTION){
            if(drag){
                piceImg->rect.x += e.motion.xrel;
                piceImg->rect.y += e.motion.yrel;
            }
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

void Pice::setClicked(bool stateClicked)
{
    if(stateClicked){
        piceImg->rect.x -= 5;
        piceImg->rect.y -= 5;
        piceImg->rect.h = PICE_DIMENSION + 10;
        piceImg->rect.w = PICE_DIMENSION + 10;
        clicked = true;
    } else{
        piceImg->rect.x += 5;
        piceImg->rect.y += 5;
        piceImg->rect.h = PICE_DIMENSION;
        piceImg->rect.w = PICE_DIMENSION;
        clicked = false;
    }
}