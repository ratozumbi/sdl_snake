//
// Created by ratozumbi on 6/24/20.
//

#ifndef ENJOIADO_ARROW_H
#define ENJOIADO_ARROW_H

#include "Actor.h"
#include "Image.h"
#include "../include/Game.h"

class Arrow : public Actor{

public:
    bool isUp = true;
    Image *pointer;
    Arrow();
    ~Arrow();
    void start();
    int update();
    int onInput(SDL_Event);
};

#endif //ENJOIADO_ARROW_H
