//
// Created by ratozumbi on 6/24/20.
//

#ifndef SDL_SNAKE_ACTOR_H
#define SDL_SNAKE_ACTOR_H

#include <SDL_events.h>
#include <atomic>

class Actor {
public:
    std::atomic<bool> active;
    Actor();
    virtual void start() {};
    virtual int update();
    virtual int onInput(SDL_Event);

protected:
    std::atomic<bool> initialized;
};

#endif //SDL_SNAKE_ACTOR_H
