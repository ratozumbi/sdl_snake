//
// Created by Rato Zumbi on 06/07/2020.
//

#include "../include/Board.h"
#include "../include/Pice.h"
#include "../include/Game.h"
#include <random>


Board::Board(): Actor(){
    colors[0] = "Color-1.png";
    colors[1] = "Color-2.png";
    colors[2] = "Color-3.png";
    colors[3] = "Color-4.png";
    colors[4] = "Color-5.png";

}
void Board::start(){

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,4);
    int dice_roll;
    int iii[5] = {1,2,3,4,5};
    char* ccolors[5] =  {"Color-11.png","Color-22.png","Color-33.png","Color-4.png","Color-5.png"};
//    std::string ccolors[5] =  {"Color-11.png","Color-22.png","Color-33.png","Color-4.png","Color-5.png"};
    std::vector<std::string> v{"Color-1.png","Color-2.png","Color-3.png","Color-4.png","Color-5.png"};
    for(int hIter = 0; hIter < BOARD_H; hIter++){
        for(int wIter = 0; wIter < BOARD_W; wIter++){
            std::string str("Color-"+std::to_string(1)+".png");
            dice_roll = distribution(generator);
            pices[hIter][wIter] = Game::scenes.at(1).loadActor<Pice>( str,hIter * 70,wIter * 70);//70x70
        }
    }
}

int Board::update(){
    Actor::update();
    return 0;
}
int Board::onInput(SDL_Event e){
    Actor::onInput(e);
//    if()
//    bool insideRect = (e.button.x >= pice->rect.x &&
//                       e.button.x <= pice->rect.x + pice->rect.w &&
//                       e.button.y >= pice->rect.y &&
//                       e.button.y <= pice->rect.y + pice->rect.h);
//
//    if(e.type == SDL_MOUSEBUTTONUP){
//
//    }
//
//    if(e.type == SDL_MOUSEMOTION){
//        if(insideRect) {
//            if(e.motion.state == SDL_BUTTON_LMASK){
//                pice->rect.x += e.motion.xrel;
//                pice->rect.y += e.motion.yrel;
//            }
//            if(e.motion.state == SDL_BUTTON_RMASK){
//
//            }
//        }
//    }
    return 0;
}

