//
// Created by Rato Zumbi on 03/07/2020.
//

#ifndef GAME_PICE_H
#define GAME_PICE_H

#include "../include/Actor.h"
#include "Image.h"

class Pice: public Actor {

public:
    bool clicked;
    Image *pice;
    Pice();
    void start();
    int update();
    int onInput(SDL_Event);

};


#endif //GAME_PICE_H