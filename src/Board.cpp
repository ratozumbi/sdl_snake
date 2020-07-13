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

/// Generates a new pice on this board at board position h and w.
/// \param h The height in the board
/// \param w The width in the board
/// \param y The pices offset above 0 where to spawn (and then fall to h)
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
    pices[h][w]->piceImg->rect.x = (w * PICE_DIMENSION) + 200;
    if(y>=0){
        y++;
        pices[h][w]->piceImg->rect.y = ((y * PICE_DIMENSION)*-1) + 100;//((y-1 * PICE_DIMENSION) * y==0?1:-1) + 100;
//        pices[h][w]->moveDown(y);
    }else
    {
        pices[h][w]->piceImg->rect.y = (h * PICE_DIMENSION) + 100;
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
    int count_chain = 0;

    PiceType piceType = PiceType::_LAST;

    int score = 0;

    //TODO: optimise these for loops

    bool chain = false;
    //W
    for (int iH = 0; iH < BOARD_H; iH++) {
        for (int iW = 0; iW < BOARD_W; iW++) {
            if (!pices[iH][iW]->isAnimating()) {
                if(piceType == pices[iH][iW]->type){
                    count_chain++;
                    if(chain){
                        score+=1;
                        pices[iH][iW]->setDestroy();
                    }
                } else{
                    count_chain=0;
                    chain = false;
                }

                if(count_chain == checkRange-1){
                    chain = true;
                    for (int i = 0; i < checkRange; i++){
                        pices[iH][iW-i]->setDestroy();
                        score +=checkRange;
                    }
                }
            }
            piceType = pices[iH][iW]->type;
        }
        piceType = PiceType::_LAST;
        chain = false;
        count_chain = 0;
    }

    chain = false;
    count_chain = 0;

    //H
    for (int iW = 0; iW < BOARD_W; iW++) {
        for (int iH = 0; iH < BOARD_H; iH++) {
            if (!pices[iH][iW]->isAnimating()) {
                if(piceType == pices[iH][iW]->type){
                    count_chain++;
                    if(chain){
                        score+=1;
                        pices[iH][iW]->setDestroy();
                    }
                } else{
                    count_chain=0;
                    chain = false;
                }

                if(count_chain == checkRange -1){
                    chain = true;
                    //destroy on the chain from beginning
                    for (int i = 0; i < checkRange; i++){
                        pices[iH-i][iW]->setDestroy();
                        score +=checkRange;
                    }
                }
            }
            piceType = pices[iH][iW]->type;
        }
        piceType = PiceType::_LAST;
        chain = false;
        count_chain = 0;
    }



//
//    if(pices[h][w]){
//        for (int i = 0; i < checkRange; i++){
//            //H
//            if(h +checkRange-i < BOARD_H && !pices[h +checkRange-i][w]->isAnimating()){ //TODO: remove second clasule?
//                if(pices[h][w]->type == pices[h +checkRange-i][w]->type){
//                    countH++;
//                    if(countH == checkRange -1){
//                        //TODO: clean this
//                        if(destoryOnCheck){
//                            pices[h][w]->setDestroy();
//                            pices[h + 1][w]->setDestroy();
//                            pices[h + 2][w]->setDestroy();
//                        }
//                        score += 3;
//                    }
//
//                    //We could add more point types for more squares here
////                    if(countH == checkRange+1){
////                        pices[h][w]->setDestroy();
////                        pices[h + 1][w]->setDestroy();
////                        pices[h + 2][w]->setDestroy();
////                        pices[h + 3][w]->setDestroy();
////                        score += 1;
////                    }
//                }
//            }
//
//            //W
//            if(w +checkRange-i < BOARD_W && !pices[h][w+checkRange-i]->isAnimating()){
//                if(pices[h][w]->type == pices[h][w+checkRange-i]->type){
//                    count_chain++;
//                    if(count_chain == checkRange-1 ){
//                        if(destoryOnCheck){
//                            pices[h][w]->setDestroy();
//                            pices[h][w + 1]->setDestroy();
//                            pices[h][w + 2]->setDestroy();
//                        }
//                        score += 3;
//                    }
//                }
//            }
//        }
//        count_chain =0;
//        countH =0;
//    }

    return score;
}

/// Swap specified pice for the one on top recursivly. If none is on top, a new pice is created in the position
/// \param h height of the pice on the board
/// \param w width of the pice on the board
/// \param _firstCall internal controller
void Board::smash(unsigned int h, unsigned int w, bool _firstCall){
    if(h >= BOARD_H || w>= BOARD_W){
        std::cout <<"error! pice to smash is out of range"<< std::endl;
        return;
    }
    if(_firstCall)
    {
        if(!pices[h][w]->getDestroy()){
            std::cout <<"error! cant smash on pice not marked to destroy"<< std::endl;
            return;
        }
//        pices[h][w]->active = false;
    }
    if(h != 0){
        pices[h][w] = pices[h-1][w];
        pices[h][w]->moveDown(1);
        smash(h - 1, w, false);
    }
    else
    {
//        pices[h][w]->active = false;
        genNew(h,w,0);
        pices[h][w]->moveDown(1);
        //update actor list on this line <<<<

//        pices[h][w]->moveDown(h);
    }


}

int Board::update(){
    Actor::update();

    static int totalScore = 0;
    int initialScore = totalScore;

    int countDestroyH =0;

    for(uint32_t  wInter = 0; wInter < BOARD_W; wInter ++) {
        for (uint32_t  hInter = 0; hInter < BOARD_H; hInter++) {
            //dont mess with moving parts
            if(pices[hInter][wInter]->isSpining == 2){
                if(pices[hInter][wInter]->getDestroy()) {
                    smash(hInter,wInter);
                    countDestroyH ++;
                }
                if(!pices[hInter][wInter]->isAnimating()){
                    initialScore += checkInRange(hInter,wInter);
                }
                //check if any pice needs to be destroyed and move to smash
//                if(pices[hInter][wInter]->getDestroy()){
//                    countDestroyH[wInter]++;
//                    smash(hInter, wInter);
//                }
//                else{
//                    //check neighbors
//                    initialScore += checkInRange(hInter,wInter);
//                }
            }
        }
//        for(int i = 0; i< countDestroyH; i++){
//            genNew(i,wInter,i);
//        }
    }

    initialScore += checkInRange(0,0);

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