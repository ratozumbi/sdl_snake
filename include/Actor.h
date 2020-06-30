//
// Created by ratozumbi on 6/24/20.
//

#ifndef SDL_SNAKE_ACTOR_H
#define SDL_SNAKE_ACTOR_H

#include <SDL_events.h>

class Actor {
public:
    bool active = true;
    Actor();
    virtual void start() {};
    virtual int update();
    virtual int onInput(SDL_Event);

protected:
    bool initialized = false;
};

#endif //SDL_SNAKE_ACTOR_H
