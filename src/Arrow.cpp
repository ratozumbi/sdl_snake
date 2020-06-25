//
// Created by ratozumbi on 6/24/20.
//

#include <iostream>
#include "../include/Arrow.h"
#include "../include/util.h"
//using Game::loadImage

Arrow::Arrow(){

};

void Arrow::update() {
    Actor::update();
    auto pointer = Game::Util::findImage("pointer.png");

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
        Game::allImages[0]->rect.y = 360;
    }
    if(e.key.keysym.sym == SDLK_DOWN){
        Game::allImages[0]->rect.y = 480;
    }

}