//
// Created by ratozumbi on 6/24/20.
//

#include "../include/Arrow.h"

Arrow::Arrow():Actor(){
    pointer = Util::findImage("pointer.png");
};

Arrow::~Arrow(){
    Game::scenes.at(Game::currentScene).deleteImage(pointer);
};

void Arrow::start() {
}

int Arrow::update() {
    Actor::update();

    static int increment = 1;

    if(pointer->rect.x <= 250 || pointer->rect.x >= 300){
        increment *= -1;
    }

    pointer->rect.x = pointer->rect.x +increment;
    return 0;
}

int Arrow::onInput(SDL_Event e) {
    Actor::onInput(e);

    if(e.key.keysym.sym == SDLK_UP){
        isUp = true;
        pointer->rect.y = 425;
    }
    if(e.key.keysym.sym == SDLK_DOWN){
        isUp = false;
        pointer->rect.y = 500;
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