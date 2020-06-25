//
// Created by ratozumbi on 6/23/20.
//

#include "../include/Image.h"

Image::Image (string name, SDL_Rect &rect1, SDL_Texture &texture): GameObject(name, rect1){

    this->texture = &texture;

}

Image::Image(string name, SDL_Rect &rect1) {
    this->name = name;
    this->rect = rect1;
}

Image::Image() { }
