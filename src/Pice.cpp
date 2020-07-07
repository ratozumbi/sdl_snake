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

Pice::~Pice() {
    delete((void*)pice);
};

void Pice::start() {
    Actor::start();
    if(pice == NULL){
        pice = Game::scenes.at(1).loadImage("Color-4.png");
    }
};

void Pice::start(char * name) {
    Actor::start();
//    pice = Game::scenes.at(1).loadImage(name);//Game::scenes.at(1).GetImage(name);
};

void Pice::start(char * name, int x, int y) {
    Actor::start();
//    pice = Game::scenes.at(1).loadImage(name, *Engine::renderer, x,y);//Game::scenes.at(1).GetImage(name);
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

    return 0;
}