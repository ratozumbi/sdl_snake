//
// Created by Rato Zumbi on 03/07/2020.
//

#include "../include/Game.h"
#include "../include/Pice.h"

Pice::Pice():Actor() {
    pice = NULL;
    clicked = false;
    active = true;
};

void Pice::start() {
    Actor::start();
    if(pice == NULL){
        pice = Game::scenes.at(1).loadImage("Color-4.png");
    }
};

void Pice::start(std::string name) {
    Actor::start();
    pice = Game::scenes.at(1).loadImage(name);//Game::scenes.at(1).GetImage(name);
};

void Pice::start(std::string name, int x, int y) {
    Actor::start();
    pice = Game::scenes.at(1).loadImage(name, *Engine::renderer, x,y);//Game::scenes.at(1).GetImage(name);
};

void Pice::start(Image* img) {
    Actor::start();
    pice = img;
};

//void Pice::start(string name) {
//    Actor::start();
//    pice = Game::scenes.at(1).loadActor<Pice>();
//};

int Pice::update(){
    Actor::update();
    return 0;
};

int Pice::onInput(SDL_Event e){
    Actor::onInput(e);
    bool insideRect = (e.button.x >= pice->rect.x &&
                       e.button.x <= pice->rect.x + pice->rect.w &&
                       e.button.y >= pice->rect.y &&
                       e.button.y <= pice->rect.y + pice->rect.h);

    if(e.type == SDL_MOUSEMOTION){
        if(insideRect) {
            if(e.motion.state == SDL_BUTTON_LMASK){
                pice->rect.x += e.motion.xrel;
                pice->rect.y += e.motion.yrel;
            }
            if(e.motion.state == SDL_BUTTON_RMASK){

            }
        }
    }
    return 0;
}