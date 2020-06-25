//
// Created by ratozumbi on 6/24/20.
//

#include "../include/Arrow.h"
//#include "../include/main.h"
//using Game::loadImage

Arrow::Arrow(){

};

void Arrow::update() {
    Actor::update();
}

void Arrow::onInput(SDL_Event e) {
    Actor::onInput(e);

//    if(e.key.keysym.sym == SDLK_UP){
//        Game::allImages[0]->rect.x = 190;
//        Game::allImages[0]->rect.y = 360;
//    }
//    if(e.key.keysym.sym == SDLK_DOWN){
//        Game::allImages[0]->rect.x = 190;
//        Game::allImages[0]->rect.y = 480;
//    }

}