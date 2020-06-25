//
// Created by ratozumbi on 6/24/20.
//

#ifndef SDL_SNAKE_ARROW_H
#define SDL_SNAKE_ARROW_H

#include "../include/Actor.h"

class Arrow:public Actor{

public:
    Arrow();
    void update();
    void onInput(SDL_Event);
};

#endif //SDL_SNAKE_ARROW_H
