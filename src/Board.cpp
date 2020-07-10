//
// Created by Rato Zumbi on 07/07/2020.
//

#include <iostream>
#include "../include/Board.h"
#include "../include/Game.h"

Board::Board():Actor() {
    for(int wInter = 0; wInter < BOARD_W; wInter ++){
        for(int hInter = 0; hInter < BOARD_W; hInter ++){
            genNew(hInter,wInter);
        }
    }
};

void Board::genNew(uint32_t hInter, uint32_t wInter){
    int typeRand = (int)(rand() % (int)PiceType::_LAST);
    PiceType type = PiceTypeToEnum[typeRand];
    pices[hInter][wInter] = Game::scenes.at(Util::findScene("game")).loadActor<Pice>(type);
    pices[hInter][wInter]->type = type; //TODO: check why object is losing type
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

//TODO: swap W and H
/// Check if sequence is activated
/// \param h The pice H in board
/// \param w The pice W in board
/// \return The socore
int Board::checkInRange(uint32_t h , uint32_t w){

    int countH = 0;
    int countW = 0;

    int score = 0;

    if(pices[h][w]){
        for (int i = 0; i < checkRange; i++){
            //H
            if(h +checkRange-i < BOARD_H && pices[h +checkRange-i][w]){ //TODO: remove second clasule?
                if(pices[h][w]->type == pices[h +checkRange-i][w]->type){
                    countH++;
                    if(countH == checkRange -1){
                        //TODO: clean this
                        pices[h][w]->setDestroy();
                        pices[h + 1][w]->setDestroy();
                        pices[h + 2][w]->setDestroy();
                        score += 3;
                    }

                    //We could add more points for more squares here
//                    if(countH == checkRange+1){
//                        pices[h][w]->setDestroy();
//                        pices[h + 1][w]->setDestroy();
//                        pices[h + 2][w]->setDestroy();
//                        pices[h + 3][w]->setDestroy();
//                        score += 4;
//                    }
                }
            }

            //W
            if(w +checkRange-i < BOARD_W && pices[h][w+checkRange-i]){
                if(pices[h][w]->type == pices[h][w+checkRange-i]->type){
                    countW++;
                    if(countW == checkRange-1 ){
                        pices[h][w]->setDestroy();
                        pices[h][w + 1]->setDestroy();
                        pices[h][w + 2]->setDestroy();
                        score += 3;
                    }
                }
            }
        }
        countW =0;
        countH =0;
    }

    return score;
}

int Board::update(){
    Actor::update();

    static int totalScore = 0;
    int initialScore = totalScore;

    for(u_int wInter = 0; wInter < BOARD_W; wInter ++) {
        for (u_int hInter = 0; hInter < BOARD_H; hInter++) {
            //dont mess with moving parts
            if(!pices[hInter][wInter]->isMoving){
                //check if any pice needs to be destroyed and move to smash
                if(pices[hInter][wInter]->getDestroy()){
                    swapUp(hInter,wInter);
                }
                //check neighbors
                initialScore += checkInRange(hInter,wInter);
            }
            else
            {
                continue;
            }
        }
    }

    if(totalScore < initialScore){
        std::cout << "TOTAL SCORE: " << totalScore << "\n"
        << " NOW SCORED: " << initialScore - totalScore << std::endl;
        totalScore += initialScore;
    }


    return 0;
};

int Board::onInput(SDL_Event e){
    Actor::onInput(e);
    return 0;
}