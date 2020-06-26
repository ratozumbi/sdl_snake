//
// Created by ratozumbi on 6/24/20.
//

#ifndef SDL_SNAKE_ARROW_H
#define SDL_SNAKE_ARROW_H

#include "Actor.h"
#include "GameObject.h"

extern bool isUp = false;

class Arrow:public Actor{

public:
    GameObject *pointer;
    Arrow();
    ~Arrow();
    void update();
    void onInput(SDL_Event);
};

#endif //SDL_SNAKE_ARROW_H
