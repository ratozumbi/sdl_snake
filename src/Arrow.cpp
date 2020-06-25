//
// Created by ratozumbi on 6/24/20.
//

#include "Arrow.h"

Arrow::Arrow(){

};

void Arrow::update() {
    Actor::update();

}
void Arrow::onInput(SDL_Event e) {
    if(e.key.keysym.sym == SDLK_UP){
//        rect.x = 190;
//        rect.y = 360;
    }
    if(e.key.keysym.sym == SDLK_DOWN){

    }

}