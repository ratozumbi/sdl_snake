//
// Created by ratozumbi on 6/23/20.
//

#ifndef SDL_SNAKE_IMAGEGAMEOBJECT_H
#define SDL_SNAKE_IMAGEGAMEOBJECT_H

#include "GameObject.h"
#include <string>


class ImageGameObject: public GameObject {

public:
    bool active = true;
    SDL_Texture *texture;
    ImageGameObject (string , SDL_Rect &, SDL_Texture &);
    ImageGameObject (SDL_Rect &, SDL_Texture &);
    ImageGameObject (SDL_Texture &);

    ImageGameObject(string name, SDL_Rect &rect1);
};


#endif //SDL_SNAKE_IMAGEGAMEOBJECT_H
