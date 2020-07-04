//
// Created by ratozumbi on 6/26/20.
//

#include "../include/Scene.h"
#include "../include/Arrow.h"

#include "../include/Game.h"

std::string name;

std::vector<Image*> images;
std::vector<Actor*> actors;

Scene::Scene(){

}

Scene::Scene(std::string name){
    this->name = name;
}

Scene::~Scene(){

}

Image *Scene::loadImage(string name, SDL_Renderer &r) {

    int w, h; // texture width & height
    SDL_Rect rect;

    auto fullPath = std::string("..\\res\\") + name;
    SDL_Texture *texture = IMG_LoadTexture(&r, fullPath.c_str());


    if (texture == NULL) {
        SDL_Log("Can't load image. %s", SDL_GetError());
        throw std::exception(); //TODO: log error
    }
    SDL_QueryTexture(texture, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle

    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;


    //TODO: check if image exists before creating a new one
    auto newImage = new Image(name.c_str(), rect, *texture);
    images.push_back(newImage);
    return newImage;
}

Image *Scene::loadImage(string name, SDL_Renderer &r, int x, int y) {
    auto newImage = loadImage(name,r);
    newImage->rect.x =x;
    newImage->rect.y =y;
    return newImage;
}

Image *Scene::loadImage(string name, SDL_Renderer &r, int x, int y, bool active) {
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
Image *Scene::GetImage(string name) {
    for(int i = 0; i < images.size(); i++){
        if(images[i]->name.compare(name) == 0){
           return images[i];
        }
    }
//    TODO: throw not found
}