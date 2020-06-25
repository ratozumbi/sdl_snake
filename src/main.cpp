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

    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_Log("Can't init %s", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow("Snake", 100, 100, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // //background
    SDL_Texture *texture = IMG_LoadTexture(renderer, "../res/fundo.png");
    SDL_QueryTexture(texture, NULL, NULL, &w, &h); // get the width and height of the texture
    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    Game::loadImage("pointer.png",0,*renderer);

    allImages[0]->rect.x = 190;
    allImages[0]->rect.y = 480; //360;

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
        SDL_RenderCopy(renderer, texture, NULL, &texr); //background
        for (int i = 0; i < 255 ; ++i) {
            if(allImages[i] != nullptr && allImages[i]->active)
            {
                SDL_RenderCopy(renderer, allImages[i]->texture, NULL, &allImages[i]->rect);
            }

        }

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
