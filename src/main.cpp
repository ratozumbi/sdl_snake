//#define SDL_MAIN_HANDLED //windows hack
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <thread>
#include <future>

#include "../include/Image.h"
#include "../include/Game.h"
#include "../include/Scene.h"
#include "../include/Pice.h"

void input(){
    std::cout<<"works";
    while(true){
        // event handling
        SDL_Event e;
        bool hasEvent = SDL_PollEvent(&e);

        if (hasEvent) {
            if (e.type == SDL_QUIT)
                try{
                    std::terminate();
                }
                catch (std::exception e) {
                    std::cout << e.what();
                }
            else if ( e.key.keysym.sym == SDLK_ESCAPE)
                try{
                    std::terminate();
                }
                catch (std::exception e) {
                    std::cout << e.what();
                }
        }

        //game update and event resolution
        //TODO: create a separate thread for inputs
        for (int i = 0; i < Game::scenes.at(Game::currentScene).GetActorsSize() ; ++i) {
            if (Game::scenes.at(Game::currentScene).GetActor(i)->active) {
                if(hasEvent){
                    if(Game::scenes.at(Game::currentScene).GetActor(i)->onInput(e) == -1){
                        try{
                            std::terminate();
                        }
                        catch (std::exception e) {
                            std::cout << e.what();
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
//    SDL_SetMainReady();
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
    Game::scenes.push_back(Scene("menu"));
    Game::scenes.push_back(Scene("game"));

    //load images
    Game::scenes.at(Util::findScene("menu")).loadImage("fundo.png", *renderer);
    Game::scenes.at(Util::findScene("menu")).loadImage("pointer.png", *renderer, 190, 360);

    Game::scenes.at(Util::findScene("game")).loadImage("Backdrop13.jpg", *renderer);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-1.png", *renderer,50,10);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-2.png", *renderer,10,40);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-3.png", *renderer,10,80);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-4.png", *renderer,10,120);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-5.png", *renderer,10,150);

    //load actors
    Game::scenes.at(Util::findScene("menu")).loadActor<Arrow>();
    Game::scenes.at(Util::findScene("game")).loadActor<Pice>();

    const int targetFPS = 60;
    const int frameDelay = 1000/ targetFPS;
    Uint32 frameStart;
    int frameTime;

    std::thread inputs (input);
    inputs.detach();

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
        //TODO: create a separate thread for inputs
        for (int i = 0; i < Game::scenes.at(Game::currentScene).GetActorsSize() ; ++i) {
            if (Game::scenes.at(Game::currentScene).GetActor(i)->active) {
                Game::scenes.at(Game::currentScene).GetActor(i)->update();

//                if(hasEvent){
//                    if(Game::scenes.at(Game::currentScene).GetActor(i)->onInput(e) == -1){
//                        playing = false;
//                    }
//                }
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
    inputs.join();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
