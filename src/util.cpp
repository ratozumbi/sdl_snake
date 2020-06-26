//
// Created by ratozumbi on 6/25/20.
//

#include "../include/util.h"
#include "../include/Arrow.h"


//Image **Game::allImages;
std::vector<Image*> Game::allImages;
std::vector<Actor*> Game::allActors;

GameObject *Game::loadImage(string name, int z, SDL_Renderer &r) {

    // load our image2
    int w, h; // texture width & height
//    char result[100];   // array to hold the result.
//    strcpy(result,"../res/"); // copy string one into the result.
//    const char * path = strcat(result,name.c_str()); // append string two to the result.

    std::string fullPath = "../res/" + name;
    SDL_Texture *texture = IMG_LoadTexture(&r, fullPath.c_str());


    if (texture == NULL) {
        SDL_Log("Can't load image. %s", SDL_GetError());
        throw std::exception(); //TODO: log error
    }
    SDL_QueryTexture(texture, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;


    //TODO: check if there is an image in z and destroy it before creating a new one
    auto newImage = new Image(name.c_str(), rect, *texture);
    Game::allImages.push_back(newImage);

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
    for(int i = 0; i< allImages.size();i++){
        if(allImages.at(i)->name.compare(name) == 0){
            return allImages.at(i);
        }
    };
}