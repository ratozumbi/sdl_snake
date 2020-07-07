//
// Created by Rato Zumbi on 03/07/2020.
//

#include <iostream>
#include "../include/Game.h"
#include "../include/Pice.h"

Image* pice;
bool clicked = false;
Pice::Pice():Actor() {

};

Pice::Pice(std::string imgName): Actor() {
    pice = Game::scenes.at(Util::findScene("game")).loadImage(imgName, *Engine::renderer, 10, 10);//Game::scenes.at(1).GetImage(imgName);
};

void Pice::start() {
};


void Pice::start(Image* img) {
    Actor::start();
    pice = img;
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