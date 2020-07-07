//
// Created by ratozumbi on 6/23/20.
//

#include "../include/GameObject.h"

GameObject::GameObject(char* name, SDL_Rect &rect1) {
    this->name = name;
    this->rect = rect1;
}

GameObject::GameObject(SDL_Rect &rect1) {
    name = "NewCustomGameObject";
    this->rect = rect1;
}

GameObject::GameObject() {
    name = "NewGameObject";
    rect.x =2;
    rect.y =2;
    rect.w =2;
    rect.h =2;
}

GameObject::~GameObject() {

}
