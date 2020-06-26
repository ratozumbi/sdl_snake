//
// Created by ratozumbi on 6/24/20.
//

#include <iostream>
#include "../include/Arrow.h"
#include "../include/util.h"
//using Game::loadImage

GameObject *pointer;
Arrow::Arrow(){
     pointer = Game::Util::findImage("pointer.png");
};

Arrow::~Arrow(){
    delete pointer;
};

void Arrow::update() {
    Actor::update();

    static int increment = 1;

    if(pointer->rect.x <= 150 || pointer->rect.x >= 190){
        increment *= -1;
    }

    pointer->rect.x = pointer->rect.x +increment;

}

void Arrow::onInput(SDL_Event e) {
    Actor::onInput(e);
;
    if(e.key.keysym.sym == SDLK_UP){
        isUp = true;
        pointer->rect.y = 360;
    }
    if(e.key.keysym.sym == SDLK_DOWN){
        isUp = false;
        pointer->rect.y = 480;
    }
    if(e.key.keysym.sym == SDLK_RETURN){
        if(isUp){

        } else{

        }
    }


}