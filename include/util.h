//
// Created by ratozumbi on 6/24/20.
//
#pragma once

#ifndef SDL_SNAKE_UTIL_H
#define SDL_SNAKE_UTIL_H

#include <vector>
#include "GameObject.h"

#include "../include/Image.h"
#include "../include/Actor.h"
#include "Arrow.h"

namespace Game {


    enum ActorType {
        ACT_Arrow,
        ACT_Actor
    };


    //extern Image **allImages[255];
    extern std::vector<Image*> allImages;
    extern std::vector<Actor*> allActors;
    //Actor *allActors[255];

    int loadImage(string, int, SDL_Renderer &);
    int loadActor(ActorType, int , ...);

    namespace Util {

        inline GameObject *findImage(std::string name){
            GameObject img;
            for(int i = 0; i< 255;i++){
                if(allImages.at(i)->name.compare(name) == 0){
                    return allImages.at(i);
                }
            };
        }


    }
}

#endif //SDL_SNAKE_UTIL_H
