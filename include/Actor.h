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
    void update();
    void onInput(SDL_Event);
};

#endif //SDL_SNAKE_ACTOR_H
