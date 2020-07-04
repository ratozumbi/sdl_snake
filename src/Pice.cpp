//
// Created by Rato Zumbi on 03/07/2020.
//

#include "../include/Game.h"
#include "../include/Pice.h"

Image* pice;
bool clicked = false;
Pice::Pice():Actor() {

};

void Pice::start() {
    Actor::start();
    pice = Game::scenes.at(Game::currentScene).GetImage("Color-1.png");
};

int Pice::update(){
    Actor::update();
    return 0;
};

int Pice::onInput(SDL_Event e){
    Actor::onInput(e);

    if(clicked && e.type == SDL_MOUSEMOTION){
        if(e.motion.state == SDL_BUTTON_LMASK){
            if(e.button.x >= pice->rect.x &&
               e.button.x <= pice->rect.x + pice->rect.w &&
               e.button.y >= pice->rect.y &&
               e.button.y <= pice->rect.y + pice->rect.h) {
                pice->rect.x += e.motion.xrel;
                pice->rect.y += e.motion.yrel;
            }
        }
    }
    return 0;
}