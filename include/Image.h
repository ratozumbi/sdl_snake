//
// Created by ratozumbi on 6/23/20.
//

#ifndef SDL_SNAKE_IMAGE_H
#define SDL_SNAKE_IMAGE_H

#include "../include/GameObject.h"
#include "GameObject.h"
#include <string>
using std::string;
#include <SDL_rect.h>
#include <SDL_system.h>


class Image: public GameObject {

public:

    SDL_Texture *texture;
    Image (string , SDL_Rect &, SDL_Texture &);
    Image();
    ~Image();

};


#endif //SDL_SNAKE_IMAGE_H
