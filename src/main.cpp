#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char **argv)
{

    int w, h; // texture width & height
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_Log("Can't init %s", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow("The Game Window2", 100, 100, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // load our image
    SDL_Texture *texture = IMG_LoadTexture(renderer, "/home/ratozumbi/repos/sdl_snake/res/fundo.png");
    SDL_QueryTexture(texture, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;


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
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

        // clear the screen
        SDL_SetRenderDrawColor(renderer,128,1,1,0);
        SDL_RenderClear(renderer);
        // copy the texture to the rendering context
        SDL_RenderCopy(renderer, texture, NULL, &texr);
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
