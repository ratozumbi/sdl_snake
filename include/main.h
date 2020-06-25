//
// Created by ratozumbi on 6/24/20.
//
#pragma once

#ifndef SDL_SNAKE_MAIN_H
#define SDL_SNAKE_MAIN_H

#include "GameObject.h"

#include "../include/Image.h"
#include "../include/Actor.h"
namespace Game {

    namespace { //"private"
        enum ActorType {
            ACT_Arrow,
            ACT_Actor
        };
    }

    Image *allImages[255];
    Actor *allActors[255];


    int loadActor(ActorType act, int n_args, ...){
        va_list ap;
        va_start(ap, n_args);

        if(act == ACT_Actor){

        }
        if(act == ACT_Arrow){

        }
        return 0;

    }

    int loadImage(string name, int z, SDL_Renderer &r) {

        // load our image2
        int w, h; // texture width & height
        char result[100];   // array to hold the result.

        strcpy(result,"../res/"); // copy string one into the result.
        const char * path = strcat(result,name.c_str()); // append string two to the result.

        SDL_Texture *texture = IMG_LoadTexture(&r, path);
        if (texture == NULL) {
            SDL_Log("Can't load image. %s", SDL_GetError());
            return 1;
        }
        SDL_QueryTexture(texture, NULL, NULL, &w, &h); // get the width and height of the texture
        // put the location where we want the texture to be drawn into a rectangle
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = w;
        rect.h = h;


        //TODO: check if there is an image in z and destroy it before creating a new one
        allImages[z] = new Image(name.c_str(), rect, *texture);

        return 0;
    }
    namespace Util {

        GameObject *findImage(std::string name){
            GameObject img;
            for(int i = 0; i< 255;i++){
                if(allImages[i]->name.compare(name) == 0){
                    return allImages[i];
                }
            };
        }


    }
}

#endif //SDL_SNAKE_MAIN_H
