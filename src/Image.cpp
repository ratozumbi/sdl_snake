//
// Created by ratozumbi on 6/23/20.
//

#include "../include/Image.h"
#include "../include/Scene.h"

Image::Image (char * name, SDL_Rect &rect1, SDL_Texture &texture): GameObject(name, rect1){
    this->texture = &texture;
}

Image::Image():GameObject() { }

Image::~Image() {
    SDL_free(this->texture);
}
