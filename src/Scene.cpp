//
// Created by ratozumbi on 6/26/20.
//

#include "../include/Scene.h"
#include "../include/Arrow.h"

#include "../include/Game.h"
#include <string>
#include <iostream>

char* name;

std::vector<Image*> images;
std::vector<Actor*> actors;

Scene::Scene(){

}

Scene::Scene(char* name){
    this->name = name;
}

Scene::~Scene(){

}

Image *Scene::loadImage(char * name, SDL_Renderer &r) {

    int w, h; // texture width & height
    SDL_Rect rect;

    //TODO: strcat is depricated, find a better solution
    char base [] = "..\\res\\";
    auto fullPath = std::strcat(base, name);
    std::cout << fullPath;

    auto findImage = Scene::GetImage(name);
    SDL_Texture *texture;
    if(findImage == NULL){
        texture = IMG_LoadTexture(&r, fullPath);
    } else{
        texture = findImage->texture;
    }

    if (texture == NULL) {
        SDL_Log("Can't load image. %s", SDL_GetError());
        throw std::exception(); //TODO: log error and gently exit
    }
    SDL_QueryTexture(texture, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle

    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;

    auto newImage = new Image(name, rect, *texture);
    images.push_back(newImage);
    return newImage;
}
Image *Scene::loadImage(char * name) {
    return loadImage(name, *Engine::renderer);
}

Image *Scene::loadImage(char * name, SDL_Renderer &r, int x, int y) {
    auto newImage = loadImage(name,r);
    newImage->rect.x =x;
    newImage->rect.y =y;
    return newImage;
}

Image *Scene::loadImage(char * name, SDL_Renderer &r, int x, int y, bool active) {
    auto newImage = loadImage(name,r);
    newImage->active = active;
    newImage->rect.x =x;
    newImage->rect.y =y;
    return newImage;
}

int Scene::GetActorsSize() {
    return actors.size();
}

int Scene::GetImagesSize() {
    return images.size();
}

Actor* Scene::GetActor(int position) {
    return actors.at(position);
//    TODO: throw not found
}

Image *Scene::GetImage(int position) {
    return images.at(position);
//    TODO: throw not found
}
Image *Scene::GetImage(char * name) {
    for(unsigned int i = 0; i < images.size(); i++){
        if(std::strcmp(images[i]->name,name) == 0){
           return images[i];
        }
    }
//    TODO: throw not found
    return NULL;
}