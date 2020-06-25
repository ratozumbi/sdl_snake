#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/Image.h"
#include "../include/main.h"

using Game::loadImage;
using Game::allImages;

int main(int argc, char **argv)
{

    int w, h; // texture width & height
    int w2, h2; // texture width & height

    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_Log("Can't init %s", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow("The Game Window2", 100, 100, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // load our image
    SDL_Texture *texture = IMG_LoadTexture(renderer, "../res/fundo.png");
    SDL_QueryTexture(texture, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    // load our image2
    SDL_Texture *texture2 = IMG_LoadTexture(renderer, "../res/pointer.png");
    SDL_QueryTexture(texture2, NULL, NULL, &w2, &h2); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    SDL_Rect texr2; texr2.x = 190; texr2.y = 360; texr2.w = w2; texr2.h = h2;

    Image *imgGameObj = new Image("pointer", texr2, *texture2);

    if (texture == NULL){
        SDL_Log("Can't load image. %s", SDL_GetError());
//        std::cout << SDL_GetError() << std::endl;
        return 1;
    }


    // main loop
    while (1) {

        // event handling
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                break;
            else if ( e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

        //set base color for renderer
        SDL_SetRenderDrawColor(renderer,128,0,0,0);
        // clear the screen
        SDL_RenderClear(renderer);
        // copy the texture to the rendering context
        SDL_RenderCopy(renderer, texture, NULL, &texr);
        for (int i = 0; i < 255 ; ++i) {
            if(allImages[i] != nullptr && allImages[i]->active)
            {
                SDL_RenderCopy(renderer, allImages[i]->texture, NULL, &allImages[i]->rect);
            }

        }
        //SDL_RenderCopy(renderer, imgGameObj.texture, NULL, &imgGameObj->rect);
        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);



//    SDL_Delay(10000);
    return 0;
}
