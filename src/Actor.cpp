//
// Created by ratozumbi on 6/24/20.
//

#include "../include/Actor.h"



Actor::Actor() {

}

int Actor::update(){
    if(!initialized){
        initialized = true;
        start();
    }
    if(!initialized) return 1;
    return 0;
}

int Actor::onInput(SDL_Event event){
    return 0;
}

void Actor::setDestroy(){
    markToDestroy = true;
}

bool Actor::getDestroy() {
    return markToDestroy;
}
