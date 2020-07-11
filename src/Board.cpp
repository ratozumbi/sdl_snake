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

void Board::genNew(uint32_t h, uint32_t w, int y){
    int typeRand = (int)(rand() % (int)PiceType::_LAST);

    //make sure to not spawn equal pices nearby
    if (h> 0 && w > 0) {
        while (pices[h][w - 1]->type == PiceTypeToEnum[typeRand] ||
                pices[h - 1][w]->type == PiceTypeToEnum[typeRand]) {
            typeRand = (int) (rand() % (int) PiceType::_LAST);
        }
    }
    if (h > 0 && w == 0) {
        while (pices[h - 1][w]->type == PiceTypeToEnum[typeRand]) {
            typeRand = (int) (rand() % (int) PiceType::_LAST);
        }
    }

    if (w > 0 && h==0) {
        while (pices[h][w - 1]->type == PiceTypeToEnum[typeRand]) {
            typeRand = (int) (rand() % (int) PiceType::_LAST);
        }
    }

    PiceType type = PiceTypeToEnum[typeRand];
    pices[h][w] = Game::scenes.at(Util::findScene("game")).loadActor<Pice>(type);
    pices[h][w]->type = type; //TODO: check why object is losing type
    pices[h][w]->piceImg->rect.x = (w * PICEHW) + 200;//TODO: make positions scalable
    if(y!=-1){
        //preciso saber quantos foram destruidos
        pices[h][w]->piceImg->rect.y = ((((BOARD_H -y)-1) * PICEHW) * y==BOARD_H?1:-1) + 100;
        pices[h][w]->moveDown(y+1);
    }else
    {
        pices[h][w]->piceImg->rect.y = (h * 70) + 100;
    }
    pices[h][w]->piceImg->active = true;
}

Board::~Board(){
    for(uint32_t wInter = 0; wInter < BOARD_W; wInter ++) {
            for (uint32_t hInter = 0; hInter < BOARD_H; hInter++) {
            pices[hInter][wInter]->setDestroy();
            pices[hInter][wInter]->active = false;
        }
    }
}

void Board::start() {
};

//TODO: swap W and H
/// Check if sequence is activated
/// \param h The pice H in board
/// \param w The pice W in board
/// \return The socore
int Board::checkInRange(uint32_t h , uint32_t w, bool destoryOnCheck = true){

    int countH = 0;
    int countW = 0;

    int score = 0;

    if(pices[h][w]){
        for (int i = 0; i < checkRange; i++){
            //H
            if(h +checkRange-i < BOARD_H && !pices[h +checkRange-i][w]->isMoving){ //TODO: remove second clasule?
                if(pices[h][w]->type == pices[h +checkRange-i][w]->type){
                    countH++;
                    if(countH == checkRange -1){
                        //TODO: clean this
                        if(destoryOnCheck){
                            pices[h][w]->setDestroy();
                            pices[h + 1][w]->setDestroy();
                            pices[h + 2][w]->setDestroy();
                            smash(h,  w);
                            smash(h + 1,  w);
                            smash(h + 2,  w);
                        }
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
            if(w +checkRange-i < BOARD_W && !pices[h][w+checkRange-i]->isMoving){
                if(pices[h][w]->type == pices[h][w+checkRange-i]->type){
                    countW++;
                    if(countW == checkRange-1 ){
                        if(destoryOnCheck){
                            pices[h][w]->setDestroy();
                            pices[h][w + 1]->setDestroy();
                            pices[h][w + 2]->setDestroy();
                            smash(h,  w);
                            smash(h,  w+1);
                            smash(h,  w+2);
                        }
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

/// Swap specified pice for the one on top recursivly. If none is on top, a new pice is created in the position
/// \param h height of the pice on the board
/// \param w width of the pice on the board
/// \param _firstCall don't touch this
int Board::smash(unsigned int h, unsigned int w, bool _firstCall = true, int _countMoveDown){
    if(h >= BOARD_H || w>= BOARD_W){
        std::cout <<"error! pice to smash is out of range"<< std::endl;
        return -1;
    }
    if(_firstCall)
    {
        if(!pices[h][w]->getDestroy()){
            std::cout <<"error! cant smash on pice not marked to destroy"<< std::endl;
            return -1;
        }
        pices[h][w]->active = false;
    }
    if(h == 0){
        genNew(0,w,_countMoveDown);
        return _countMoveDown;
    } else{
        pices[h][w] = pices[h-1][w];
//        pices[h][w]->moveDown(h);
        smash(h - 1, w, false, ++_countMoveDown);
    }
}

int Board::update(){
    Actor::update();

    static int totalScore = 0;
    int initialScore = totalScore;

    for(uint32_t  wInter = 0; wInter < BOARD_W; wInter ++) {
        for (uint32_t  hInter = 0; hInter < BOARD_H; hInter++) {
            //dont mess with moving parts
            if(!pices[hInter][wInter]->isMoving){
                //check if any pice needs to be destroyed and move to smash
                if(pices[hInter][wInter]->getDestroy()){
                    smash(hInter, wInter);
                }
                else{
                    //check neighbors
                    initialScore += checkInRange(hInter,wInter);
                }
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