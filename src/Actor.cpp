//
// Created by ratozumbi on 6/24/20.
//

#include <iostream>
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
    std::cout << "SET TO DESTROY" << std::endl;
    markToDestroy = true;
}
