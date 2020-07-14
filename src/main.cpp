
#include <iostream>
#include <SDL.h>

#include <thread>

#include "../include/Image.h"
#include "../include/Game.h"
#include "../include/Board.h"

void exitGame(){
    std::cerr<< "END GAME";

    Game::scenes.clear();
    SDL_DestroyRenderer(Engine::renderer);
    SDL_DestroyWindow(Engine::window);
    std::exit(0);
}

//inputs where not smooth in the main thread
//TODO: double check if this is needed
void input(){
    bool running = true;
    while(running){
        // event handling
        SDL_Event e;
        bool hasEvent = SDL_PollEvent(&e);

        static bool lockBtnLeft = false;//dont let update happen on repeated mouse inputs
        if (hasEvent) {
            switch (e.type){
                case SDL_QUIT:
                    running = false;
                    exitGame();
                    break;
                case SDL_KEYDOWN:
                    //TODO: #BUG 1 esc key freezes the game
                    if ( e.key.keysym.sym == SDLK_F1){
                        running = false;
                        exitGame();
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_LEFT){
                        if(lockBtnLeft)
                            return;
                        lockBtnLeft = true;
                    }else if(e.type == SDL_MOUSEBUTTONUP){
                        if(e.button.button == SDL_BUTTON_LEFT){
                            lockBtnLeft = false;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(e.button.button == SDL_BUTTON_LEFT){
                        lockBtnLeft = false;
                    }
                    break;
            }

            for (int i = 0; i < Game::scenes.at(Game::currentScene).getActorsSize() ; ++i) {
                if (Game::scenes.at(Game::currentScene).getActor(i)->active) {
                    if(Game::scenes.at(Game::currentScene).getActor(i)->onInput(e) == -1){
                        running = false;
                        exitGame();
                    }
                }
            }
        }
    }

}

int main(int argc, char **argv) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Can't init %s", SDL_GetError());
        return 1;
    }
    Engine::window = SDL_CreateWindow("Snake", 50, 50, 1024, 768, 0);
    Engine::renderer = SDL_CreateRenderer(Engine::window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize scenes
    Game::scenes.push_back(Scene("menu"));
    Game::scenes.push_back(Scene("game"));

    //load images
    Game::scenes.at(Util::findScene("menu")).loadImage("menu.jpeg");
    Game::scenes.at(Util::findScene("menu")).loadImage("pointer.png", 300, 425);

    Game::scenes.at(Util::findScene("game")).loadImage("Backdrop13.jpg");

    //load actors
    Game::scenes.at(Util::findScene("menu")).loadActor<Arrow>();

    Game::scenes.at(Util::findScene("game")).loadActor<Board>();

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
        Game::scenes.at(Game::currentScene).update();

        //set base color for renderer
        SDL_SetRenderDrawColor(Engine::renderer, 128, 0, 0, 0);
        // clear the screen
        SDL_RenderClear(Engine::renderer);
        // copy the texture to the rendering context
        for (int currImg = 0; currImg < Game::scenes.at(Game::currentScene).getImagesSize(); ++currImg) {
            if (Game::scenes.at(Game::currentScene).getImage(currImg) != NULL &&
                Game::scenes.at(Game::currentScene).getImage(currImg)->active) {
                SDL_RenderCopyEx(Engine::renderer, Game::scenes.at(Game::currentScene).getImage(currImg)->texture, NULL,
                                 &Game::scenes.at(Game::currentScene).getImage(currImg)->rect,
                                 Game::scenes.at(Game::currentScene).getImage(currImg)->angle,
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
