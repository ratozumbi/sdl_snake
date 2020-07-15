//
// Created by ratozumbi on 6/26/20.
//

#include <algorithm>
#include "../include/Scene.h"
#include "../include/Arrow.h"


Scene::Scene(){

}

Scene::Scene(std::string name){
    this->name = name;
}

Scene::~Scene(){
    deleteActors();
    deleteImages();
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
        SDL_Event sdlevent;
        sdlevent.type = SDL_QUIT;
        SDL_PushEvent(&sdlevent);
        return nullptr;
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

int Scene::getActorsSize() {
    return actors.size();
}

int Scene::getImagesSize() {
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

void Scene::deleteImage(int Iimg) {
    delete (images.at(Iimg));
    images.erase(images.begin());
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

Image *Scene::getImage(int position) {
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

void Scene::deleteActors() {
    while(actors.begin()!=actors.end()){
        deleteActor(0);
    }
}

void Scene::deleteImages() {
    while(images.begin()!=images.end()){
        deleteImage(0);
    }
}

/// The given img will have Z position and the element on Z will swap with whatever position img is
/// \param img The image pointer to move
/// \param z The Z that image will have
void Scene::setZindex(Image* img, uint32_t z){
    std::vector<Image*>::iterator it =
            std::find_if(images.begin(), images.end(), [&,img](Image* e) { return (int)e == (int)img; });

    if (it != images.end()) {
        if(z>= images.size()) z = images.size()-1;
        std::iter_swap(it,images.begin()+z);
    }
}

/// Get Z of given image
/// \param img The image
/// \return The Z index
uint32_t Scene::getZindex(Image* img){
    std::vector<Image*>::iterator it =
            std::find_if(images.begin(), images.end(), [&,img](Image* e) { return (int)e == (int)img; });

    if (it != images.end()) {
        uint32_t indx = std::distance(images.begin(),it);
        return indx;
    }
}