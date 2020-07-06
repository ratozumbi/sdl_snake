#define SDL_MAIN_HANDLED //windows hack
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <thread>
#include <future>

#include "../include/Image.h"
#include "../include/Game.h"
#include "../include/Scene.h"
#include "../include/Board.h"

void exitGame(){
    std::cerr<< "END GAME";

//    SDL_DestroyTexture(texture); TODO: free images and actors
    SDL_DestroyRenderer(Engine::renderer);
    SDL_DestroyWindow(Engine::window);
}
//inputs where not smooth in the main thread
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
                std::exit(0);
            }
            //TODO: #BUG 1 find ghost esc key. Maybe the solution in on Pice's mouse
//            else if ( e.key.keysym.sym == SDLK_ESCAPE)
//            {
//                running = false;
//            }
        }

        //game event resolution
        for (int i = 0; i < Game::scenes.at(Game::currentScene).GetActorsSize() ; ++i) {
            if (Game::scenes.at(Game::currentScene).GetActor(i)->active) {
                if(hasEvent){
                    if(Game::scenes.at(Game::currentScene).GetActor(i)->onInput(e) == -1){
                        running = false;
                        exitGame();
                        std::exit(0);
                    }
                }
            }
        }
    }

    std::cout<<"off";
}

int main(int argc, char **argv) {
    SDL_SetMainReady();
    std::set_terminate(exitGame);
    std::string ccolors[5] =  {"Color-1.png","Color-2.png","Color-3.png","Color-4.png","Color-5.png"};
    std::vector<std::string> v {"Color-11.png","Color-22.png","Color-3.png","Color-4.png","Color-5.png"};
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Can't init %s", SDL_GetError());
        return 1;
    }

    Engine::window = SDL_CreateWindow("Enjoiado", 100, 100, 1024, 768, 0);
    Engine::renderer = SDL_CreateRenderer(Engine::window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize scenes
    //TODO: encapsulate scene creation (create loadScene)
    Game::scenes.push_back(Scene("menu"));
    Game::scenes.push_back(Scene("game"));

    //load images
    Game::scenes.at(Util::findScene("menu")).loadImage("fundo.png", *Engine::renderer);
    Game::scenes.at(Util::findScene("menu")).loadImage("pointer.png", *Engine::renderer, 190, 360);
    Game::scenes.at(Util::findScene("menu")).loadImage("pointer.png", *Engine::renderer, 0, 0);

    Game::scenes.at(Util::findScene("game")).loadImage("Backdrop13.jpg", *Engine::renderer);
//    auto img = Game::scenes.at(Util::findScene("game")).loadImage("Color-1.png", *Engine::renderer, 10, 10);
//    Game::scenes.at(Util::findScene("game")).loadImage("Color-2.png", *Engine::renderer, 10, 40);
//    Game::scenes.at(Util::findScene("game")).loadImage("Color-3.png", *Engine::renderer, 10, 80);
//    Game::scenes.at(Util::findScene("game")).loadImage("Color-4.png", *Engine::renderer, 10, 120);
//    Game::scenes.at(Util::findScene("game")).loadImage("Color-5.png", *Engine::renderer, 10, 150);

    //load actors
    Game::scenes.at(Util::findScene("menu")).loadActor<Arrow>();
    Game::scenes.at(Util::findScene("menu")).loadActor<Arrow>();

//    auto b = new Board();
////    b->start();
//    Game::scenes.at(Util::findScene("game")).actors.push_back(b);
//    Game::scenes.at(Util::findScene("game")).loadActor<Board>();

//    Game::scenes.at(Util::findScene("game")).loadActor<Pice>();
//    Game::scenes.at(Util::findScene("game")).loadActor<Pice>("Color-1.png",10,10);
//    Game::scenes.at(Util::findScene("game")).loadActor<Pice>("Color-2.png",100,100);
//    Game::scenes.at(Util::findScene("game")).loadActor<Pice>("Color-2.png",200,200);
//    Game::scenes.at(Util::findScene("game")).loadActor(new Pice(),img);
//    Game::scenes.at(Util::findScene("game")).loadActor(new Pice(),"Color-2.png");
//    Game::scenes.at(Util::findScene("game")).loadActor(new Pice(),"Color-3.png");
//    Game::scenes.at(Util::findScene("game")).loadActor(new Pice(),"Color-4.png");
//    Game::scenes.at(Util::findScene("game")).loadActor(new Pice(),"Color-5.png");

    //FPS control
    const int targetFPS = 60;
    const int frameDelay = 1000 / targetFPS;
    Uint32 frameStart;
    int frameTime;

    //inputs where not smooth in the main thread
    std::thread inputs(input);
    inputs.detach();

    // main loop
    bool playing = true;
    while (playing) {
        //FPS control
        frameStart = SDL_GetTicks();

        // event handling
        SDL_PumpEvents();//required to poll events in another thread

        //game actors update
        for (int i = 0; i < Game::scenes.at(Game::currentScene).GetActorsSize(); ++i) {
            if (Game::scenes.at(Game::currentScene).GetActor(i)->active) {
                Game::scenes.at(Game::currentScene).GetActor(i)->update();
            }
        }

        //set base color for renderer
        SDL_SetRenderDrawColor(Engine::renderer, 128, 0, 0, 0);
        // clear the screen
        SDL_RenderClear(Engine::renderer);
        // copy the texture to the rendering context
        for (int currImg = 0; currImg < Game::scenes.at(Game::currentScene).GetImagesSize(); ++currImg) {
            if (Game::scenes.at(Game::currentScene).GetImage(currImg) != NULL &&
                Game::scenes.at(Game::currentScene).GetImage(currImg)->active) {
                SDL_RenderCopy(Engine::renderer, Game::scenes.at(Game::currentScene).GetImage(currImg)->texture, NULL,
                               &Game::scenes.at(Game::currentScene).GetImage(currImg)->rect);
            }
        }

        //render the renderer
        SDL_RenderPresent(Engine::renderer);

        //60 FPS cap
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}
