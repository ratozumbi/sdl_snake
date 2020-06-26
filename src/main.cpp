#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/Image.h"
#include "../include/util.h"

//using Game::allImages;

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

    // Initialize scenes
    for (int currScn = (int)Game::Scene::SCN_Menu; currScn != (int)Game::Scene::SCN_ExitGame; currScn++ )
    {
        Game::allImages.push_back(std::vector<Image*>());
    }
    //load images
    Game::loadImage("fundo.png", Game::Scene::SCN_Menu,*renderer);
    Game::loadImage("pointer.png", Game::Scene::SCN_Menu,*renderer, 190,360);
    Game::loadImage("canvas.png", Game::Scene::SCN_Game,*renderer);

    //load actors
    Game::loadActor(Game::ACT_Arrow,0);

    const int targetFPS = 60;
    const int frameDelay = 1000/ targetFPS;
    Uint32 frameStart;
    int frameTime;

    // main loop
    while (1) {

        frameStart = SDL_GetTicks();

        SDL_Event e;
        //game update
        for (int i = 0; i < Game::allActors.size() ; ++i) {
            if (Game::allActors[i]->active) {
                Game::allActors[i]->update();
            }
        }

        // event handling
        if ( SDL_PollEvent(&e) ) {
            for (int i = 0; i < Game::allActors.size() ; ++i) {
                if(Game::allActors[i]->active){
                    Game::allActors[i]->onInput(e);
                }
            }
            if(Game::currentScene == Game::Scene::SCN_ExitGame){
                break;
            }
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
//        SDL_RenderCopy(renderer, texture, NULL, &texr); //background
        for (int i = 0; i < Game::allImages.at((int)Game::currentScene).size() ; ++i) {
            if(Game::allImages.at((int)Game::currentScene).at(i) != NULL && Game::allImages.at((int)Game::currentScene).at(i)->active)
            {
                SDL_RenderCopy(renderer, Game::allImages.at((int)Game::currentScene).at(i)->texture, NULL, &Game::allImages.at((int)Game::currentScene).at(i)->rect);
            }
        }

        //render the renderer
        SDL_RenderPresent(renderer);

        //60 FPS cap
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }

//    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);



//    SDL_Delay(10000);
    return 0;
}
