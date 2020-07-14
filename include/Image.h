//
// Created by ratozumbi on 6/23/20.
//

#ifndef ENJOIADO_IMAGE_H
#define ENJOIADO_IMAGE_H

#include "../include/GameObject.h"
#include "GameObject.h"
#include <string>
using std::string;
#include <SDL_rect.h>


class Image: public GameObject {

public:

    SDL_Texture *texture;
    int angle;
    Image (string , SDL_Rect &, SDL_Texture &);
    Image();
    ~Image();

};


#endif //ENJOIADO_IMAGE_H
