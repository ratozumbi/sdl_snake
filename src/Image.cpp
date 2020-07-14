//
// Created by ratozumbi on 6/23/20.
//

#include "../include/Image.h"
#include "../include/Scene.h"

Image::Image (string name, SDL_Rect &rect1, SDL_Texture &texture): GameObject(name, rect1){
    angle = 0;
    this->texture = &texture;
}

Image::Image():GameObject() { }

Image::~Image() {
    //don't delete texture as it might be used be others
}
