//
// Created by Rato Zumbi on 07/07/2020.
//

#include <iostream>
#include "../include/Board.h"
#include "../include/Game.h"

char * getRandomColor(){
    char * colors[]= {"Color-1.png","Color-2.png","Color-3.png","Color-4.png","Color-5.png"};
    return colors[rand() % 5];
}


Board::Board():Actor() {
    for(int wInter = 0; wInter < BOARD_W; wInter ++){
        for(int hInter = 0; hInter < BOARD_W; hInter ++){
            genNew(hInter,wInter);
        }
    }
};

void Board::genNew(int hInter, int wInter){
    pices[hInter][wInter] = Game::scenes.at(Util::findScene("game")).loadActor<Pice>(getRandomColor());
    pices[hInter][wInter]->piceImg->rect.x = (wInter * 70) + 200;//TODO: make positions scalable
    pices[hInter][wInter]->piceImg->rect.y = (hInter * 70) + 100;
    pices[hInter][wInter]->piceImg->active = true;
}

Board::~Board(){
    for(u_int wInter = 0; wInter < BOARD_W; wInter ++) {
        for (u_int hInter = 0; hInter < BOARD_H; hInter++) {
            pices[hInter][wInter]->setDestroy();
            pices[hInter][wInter]->active = false;
        }
    }
}

void Board::start() {
};

/// Swap specified pice for the one on top. If none is on top, a new pice is created in this position
/// \param h height of the pice on the board
/// \param w width of the pice on the board
/// \param _firstCall don't touch this
void Board::swapUp(unsigned int h, unsigned int w, bool _firstCall = true){
    if(h >= BOARD_H || w>= BOARD_W){
        std::cout <<"error! pice to swap is out of range"<< std::endl;
        return;
    }
    if(_firstCall)
    {
        if(!pices[h][w]->getDestroy()){
            std::cout <<"error! swap on pice not marked to destroy"<< std::endl;
            return;
        }
        pices[h][w]->active = false;
    }
    if(h == 0){
        genNew(0,w);
    } else{
        pices[h][w] = pices[h-1][w];
        pices[h][w]->moveDown();
        swapUp(h-1,w,false);
    }
}

int Board::update(){
    Actor::update();

    for(u_int wInter = 0; wInter < BOARD_W; wInter ++) {
        for (u_int hInter = 0; hInter < BOARD_H; hInter++) {
            //check if any pice needs to be destroyed and move to fall
            if(pices[hInter][wInter]->getDestroy()){
                swapUp(hInter,wInter);
            }
        }
    }

    return 0;
};

int Board::onInput(SDL_Event e){
    Actor::onInput(e);
    return 0;
}