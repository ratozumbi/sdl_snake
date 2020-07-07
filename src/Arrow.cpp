//
// Created by ratozumbi on 6/24/20.
//

#include <iostream>
#include "../include/Arrow.h"
#include "../include/Game.h"
//using Game::loadImage

Image *pointer;
Arrow::Arrow():Actor(){

};

Arrow::~Arrow(){
//    delete pointer;
};

void Arrow::start() {
    Actor::start();
    char* images[] = {{"pointer.png"}, {"Color-1.png"}, {"bbbbbbbbb"}};

    pointer = Game::scenes.at(0).loadImage(images[1]);
    std::cout <<"start";
}

int Arrow::update() {
    Actor::update();

    static int increment = 1;
    std::cout <<"update";
    if(pointer->rect.x <= 150 || pointer->rect.x >= 190){
        increment *= -1;
    }

    pointer->rect.x = pointer->rect.x +increment;
    return 0;
}

int Arrow::onInput(SDL_Event e) {
    Actor::onInput(e);

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
            Game::currentScene = Util::findScene("game");
        } else{
            return -1;
        }
    }

    return 0;
}