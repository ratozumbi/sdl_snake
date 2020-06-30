//
// Created by ratozumbi on 6/24/20.
//

#ifndef SDL_SNAKE_ARROW_H
#define SDL_SNAKE_ARROW_H

#include "Actor.h"
#include "Image.h"

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

#endif //SDL_SNAKE_ARROW_H
