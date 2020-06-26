//
// Created by ratozumbi on 6/25/20.
//

#include "../include/util.h"
#include "../include/Arrow.h"

//Image **Game::allImages;
std::vector<std::vector<Image*>> Game::allImages;
std::vector<Actor*> Game::allActors;
Game::Scene Game::currentScene; //TODO: Find a better place to Scene enum

//TODO: Make this enum a class or losen Game to scope wide namespace

GameObject *Game::loadImage(string name, Scene scene, SDL_Renderer &r) {

    int w, h; // texture width & height
    SDL_Rect rect;

    std::string fullPath = "../res/" + name;
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
    Game::allImages.at((int)scene).push_back(newImage);
    return newImage;
}

int Game::loadActor(ActorType act, int n_args, ...){
    va_list ap;
    va_start(ap, n_args);

    if(act == ACT_Actor){
        Game::allActors.push_back(new Actor());
    }
    if(act == ACT_Arrow){
        Game::allActors.push_back(new Arrow());
    }
    return 0;

}

GameObject *Game::Util::findImage(std::string name){
    GameObject img;
    for(int iScene = 0; iScene < allImages.size(); iScene++){
        for(int iImage = 0; iImage < allImages.at(iScene).size(); iImage++){
            if(Game::allImages.at(iScene).at(iImage)->name.compare(name) == 0){
                return Game::allImages[iScene][iImage];
            }
        }
    }
}