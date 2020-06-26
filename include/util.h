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

    enum class Scene {
        SCN_Menu,
        //scenes goes here
        SCN_Game,
        //end of scenes
        SCN_ExitGame,
    };


    //extern Image **allImages[255];
    extern Scene currentScene;
    extern std::vector<std::vector<Image*>> allImages;
    extern std::vector<Actor*> allActors;
    //Actor *allActors[255];

    GameObject *loadImage(string, Scene, SDL_Renderer &);
    GameObject *loadImage(string, Scene, SDL_Renderer &, int, int);
    int loadActor(ActorType, int , ...);

    namespace Util {

        GameObject *findImage(std::string );


    }
}

#endif //SDL_SNAKE_UTIL_H
