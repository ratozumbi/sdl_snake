#define SDL_MAIN_HANDLED //windows hack
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <thread>
#include <future>

#include "../include/Image.h"
#include "../include/Game.h"
#include "../include/Scene.h"
#include "../include/Pice.h"
#include "../include/Board.h"

void exitGame(){
    std::cerr<< "END GAME";

//    SDL_DestroyTexture(texture); TODO: free images and actors
    SDL_DestroyRenderer(Engine::renderer);
    SDL_DestroyWindow(Engine::window);
    std::exit(0);
}

//inputs where not smooth in the main thread
//TODO: double check if this is needed
void input(){
    std::cout<<"works" << std::endl;
    bool running = true;
    while(running){
        // event handling
        SDL_Event e;
        bool hasEvent = SDL_PollEvent(&e);

        if (hasEvent) {
            if (e.type == SDL_QUIT){
                running = false;
                exitGame();
            }
            //TODO: #BUG 1 esc key freezes the game
            else if ( e.key.keysym.sym == SDLK_F1)
            {
                running = false;
                exitGame();
            }
            else if ( e.key.keysym.sym == SDLK_1)
            {
                Game::scenes.at(1).deleteActor(1);
            }

            for (int i = 0; i < Game::scenes.at(Game::currentScene).GetActorsSize() ; ++i) {
                if (Game::scenes.at(Game::currentScene).getActor(i)->active) {
                    if(Game::scenes.at(Game::currentScene).getActor(i)->onInput(e) == -1){
                        running = false;
                        exitGame();
                    }
                }
            }
        }
    }

    std::cout<<"off";
}

int main(int argc, char **argv) {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Can't init %s", SDL_GetError());
        return 1;
    }
    Engine::window = SDL_CreateWindow("Snake", 100, 100, 1024, 768, 0);
    Engine::renderer = SDL_CreateRenderer(Engine::window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize scenes
    //TODO: encapsulate scene creation (create loadScene)
    Game::scenes.push_back(Scene("menu"));
    Game::scenes.push_back(Scene("game"));

    //load images
    Game::scenes.at(Util::findScene("menu")).loadImage("menu.jpeg");
    Game::scenes.at(Util::findScene("menu")).loadImage("pointer.png", 300, 425);

    Game::scenes.at(Util::findScene("game")).loadImage("Backdrop13.jpg");
    Game::scenes.at(Util::findScene("game")).loadImage("Color-1.png", 10, 10, false);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-2.png", 10, 70, false);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-3.png", 10, 140, false);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-4.png", 10, 210, false);
    Game::scenes.at(Util::findScene("game")).loadImage("Color-5.png", 10, 280, false);

    //load actors
    Game::scenes.at(Util::findScene("menu")).loadActor<Arrow>();

    Game::scenes.at(Util::findScene("game")).loadActor<Board>();
//    Arrow *b = dynamic_cast<Arrow*>(a);//(Game::scenes.at(Util::findScene("menu")).getActor(0));
//    if (b) {
//        if (b->pointer) {
//            b->pointer->rect.y = 0;
//        }
//    }
//    Arrow a = Actor();
//    Game::scenes.at(Util::findScene("game")).loadActor<Pice>("Color-1.png");


    //inputs where not smooth in the main thread
    std::thread inputs(input);
    inputs.detach();

    // main loop
    bool playing = true;
    while (playing) {
        //FPS control
        Uint32 frameStart = SDL_GetTicks();
        int frameTime;

        // event handling
        SDL_PumpEvents();//required to poll events in another thread

        //game update
        //TODO: use vector iterator to make it more readable
//        for (int i = 0; i < Game::scenes.at(Game::currentScene).GetActorsSize(); ++i) {
            Game::scenes.at(Game::currentScene).update();
//        }

        //set base color for renderer
        SDL_SetRenderDrawColor(Engine::renderer, 128, 0, 0, 0);
        // clear the screen
        SDL_RenderClear(Engine::renderer);
        // copy the texture to the rendering context
        for (int currImg = 0; currImg < Game::scenes.at(Game::currentScene).GetImagesSize(); ++currImg) {
            if (Game::scenes.at(Game::currentScene).GetImage(currImg) != NULL &&
                Game::scenes.at(Game::currentScene).GetImage(currImg)->active) {
                SDL_RenderCopyEx(Engine::renderer, Game::scenes.at(Game::currentScene).GetImage(currImg)->texture, NULL,
                               &Game::scenes.at(Game::currentScene).GetImage(currImg)->rect,
                                 Game::scenes.at(Game::currentScene).GetImage(currImg)->angle,
                                 NULL,SDL_FLIP_NONE);
            }
        }

        //render the renderer
        SDL_RenderPresent(Engine::renderer);

        //60 FPS cap
        frameTime = SDL_GetTicks() - frameStart;
        if (Engine::frameDelay > frameTime) {
            SDL_Delay(Engine::frameDelay - frameTime);
        }
    }

    return 0;
}
