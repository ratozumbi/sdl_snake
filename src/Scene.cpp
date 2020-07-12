//
// Created by ratozumbi on 6/26/20.
//

#include <algorithm>
#include <iostream>
#include "../include/Scene.h"
#include "../include/Arrow.h"

#include "../include/Game.h"

//std::string name;
//
//std::vector<Image*> images;
//std::vector<Actor*> actors;

Scene::Scene(){

}

Scene::Scene(std::string name){
    this->name = name;
}

Scene::~Scene(){

}

Image *Scene::loadImage(string name) {

    int w, h; // texture width & height
    SDL_Rect rect;

    auto fullPath = std::string("..\\res\\") + name;
    auto findImage = Scene::getImage(name);
    SDL_Texture *texture;

    //don't load textures already loaded
    if(findImage == nullptr){
        texture = IMG_LoadTexture(Engine::renderer, fullPath.c_str());
    } else{
        texture = findImage->texture;
    }

    if (texture == nullptr) {
        SDL_Log("Can't load image. %s", SDL_GetError());
        throw std::exception(); //TODO: gracefuly exits
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle

    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;

    auto newImage = new Image(name.c_str(), rect, *texture);
    images.push_back(newImage);
    return newImage;
}

Image *Scene::loadImage(string name, int x, int y) {
    auto newImage = loadImage(name);
    newImage->rect.x =x;
    newImage->rect.y =y;
    return newImage;
}

Image *Scene::loadImage(string name, int x, int y, bool active) {
    auto newImage = loadImage(name);
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

Actor* Scene::getActor(int position) {
    return actors.at(position);
//    TODO: throw not found
}

//TODO: inputUpdate for scene
int Scene::update() {
    int retCode = 0;
    for (unsigned int i = 0; i < actors.size(); ++i) {
        if(actors.at(i)->getDestroy() && actors.at(i)->active == false){
            deleteActor(actors.at(i));
        }
        if (actors.at(i)->active) {
            retCode =actors.at(i)->update();
        }

    }
    return retCode;
}

void Scene::deleteActor() {
    delete (actors.at(0));
    actors.erase(actors.begin());
}

void Scene::deleteActor(int iAct) {
    delete (actors.at(iAct));
    actors.erase(actors.begin() + iAct);
}

void Scene::deleteActor(Actor *act) {

    std::vector<Actor*>::iterator it =
            std::find_if(actors.begin(), actors.end(), [&,act](Actor* e) { return e == act; });
    if (it != actors.end()) {
        int indx = std::distance(actors.begin(),it);
        delete (actors.at(indx));
        actors.erase(it);
    }
//    TODO: throw not found
}

void Scene::deleteImage(Image *img) {
    std::vector<Image*>::iterator it =
            std::find_if(images.begin(), images.end(), [&,img](Image* e) { return (int)e == (int)img; });
    if (it != images.end()) {
        int indx = std::distance(images.begin(),it);
        delete (images.at(indx));
        images.erase(it);
    }
//    TODO: throw not found
}

Image *Scene::GetImage(int position) {
    return images.at(position);
//    TODO: throw not found
}
Image *Scene::getImage(string name) {
    for(unsigned int i = 0; i < images.size(); i++){
        if(images[i]->name.compare(name) == 0){
           return images[i];
        }
    }
//    TODO: throw not found
    return nullptr;
}