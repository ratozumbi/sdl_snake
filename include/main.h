//
// Created by ratozumbi on 6/24/20.
//

#ifndef SDL_SNAKE_MAIN_H
#define SDL_SNAKE_MAIN_H

#include "GameObject.h"

#define RES_PATH "../res/"

#include "../include/Image.h"
namespace Game {

    namespace { //"private"

    }

    Image *allImages[255];

    int loadImage(string name, int z, SDL_Renderer &r) {

        // load our image2
        int w, h; // texture width & height
        SDL_Texture *texture = IMG_LoadTexture(&r, strcat(RES_PATH,name.c_str()));
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
//        Image *imgGameObj = new Image(name, rect, *texture);
//        allImages[z] = imgGameObj;
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
