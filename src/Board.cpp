//
// Created by Rato Zumbi on 07/07/2020.
//

#include "../include/Board.h"
#include "../include/Game.h"

Board::Board():Actor() {
    char * colors[]= {"Color-1.png","Color-2.png","Color-3.png","Color-4.png","Color-5.png"};
    for(int wInter = 0; wInter < BOARD_W; wInter ++){
        for(int hInter = 0; hInter < BOARD_W; hInter ++){
            Game::scenes.at(Util::findScene("game")).loadActor<Pice>(colors[0]);
//            pices[hInter][wInter] = Game::scenes.at(Util::findScene("game"))
        }
    }
};

void Board::start() {
};

int Board::update(){
    Actor::update();
    return 0;
};

int Board::onInput(SDL_Event e){
    Actor::onInput(e);
    return 0;
}