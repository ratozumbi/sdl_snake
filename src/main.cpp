#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/Image.h"
#include "../include/Game.h"
#include "../include/Scene.h"


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
    //TODO: encapsulate scene creation (create loadScene)
//    auto menu = Scene("menu");
    Game::scenes.push_back(Scene("menu"));
//    Game::currentScene = &Game::scenes.at(0);
    Game::scenes.push_back(Scene("game"));

    //load images
    Game::scenes.at(0).loadImage("fundo.png", *renderer);
    Game::scenes.at(0).loadImage("pointer.png", *renderer, 190, 360);


    //load actors
    Game::scenes.at(0).loadActor<Arrow>();
//    Game::currentScene->actors.push_back(Arrow());

    const int targetFPS = 60;
    const int frameDelay = 1000/ targetFPS;
    Uint32 frameStart;
    int frameTime;

    // main loop
    bool playing = true;
    while (playing) {
        //FPS control
        frameStart = SDL_GetTicks();

        // event handling
        SDL_Event e;
        bool hasEvent = SDL_PollEvent(&e);
        if (hasEvent) {
            if (e.type == SDL_QUIT)
                break;
            else if ( e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

        //game update and event resolution
        for (int i = 0; i < Game::scenes.at(Game::currentScene).GetActorsSize() ; ++i) {
            if (Game::scenes.at(Game::currentScene).GetActor(i).active) {
                Game::scenes.at(Game::currentScene).GetActor(i).update();
                if(hasEvent){
                    if(Game::scenes.at(Game::currentScene).GetActor(i).onInput(e) == -1){
                        playing = false;
                    }
                }
            }

        }

        //set base color for renderer
        SDL_SetRenderDrawColor(renderer,128,0,0,0);
        // clear the screen
        SDL_RenderClear(renderer);
        // copy the texture to the rendering context
        for (int currImg = 0; currImg < Game::scenes.at(Game::currentScene).GetImagesSize() ; ++currImg) {
            if(Game::scenes.at(Game::currentScene).GetImage(currImg) != NULL && Game::scenes.at(Game::currentScene).GetImage(currImg)->active)
            {
                SDL_RenderCopy(renderer, Game::scenes.at(Game::currentScene).GetImage(currImg)->texture, NULL, &Game::scenes.at(Game::currentScene).GetImage(currImg)->rect);
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

//    SDL_DestroyTexture(texture); TODO: free textures
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
