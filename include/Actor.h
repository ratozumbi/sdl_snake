//
// Created by ratozumbi on 6/24/20.
//

#ifndef ENJOIADO_ACTOR_H
#define ENJOIADO_ACTOR_H

#include <SDL_events.h>
#include "../include/Types.h"

class Actor {
public:
    bool active = true;
    Actor();
    virtual ~Actor() {};
    virtual void start() {};
    virtual int update();
    virtual int onInput(SDL_Event);
    virtual void setDestroy();
    virtual bool getDestroy();

protected:
    bool initialized = false;
    bool markToDestroy = false;
};

#endif //ENJOIADO_ACTOR_H
