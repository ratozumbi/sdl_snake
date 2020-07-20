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
        while (pices[h][w - 1]->type == piceTypeToEnum[typeRand] ||
               pices[h - 1][w]->type == piceTypeToEnum[typeRand]) {
            typeRand = (int) (rand() % (int) PiceType::_LAST);
        }
    }
    if (h > 0 && w == 0) {
        while (pices[h - 1][w]->type == piceTypeToEnum[typeRand]) {
            typeRand = (int) (rand() % (int) PiceType::_LAST);
        }
    }
    if (w > 0 && h==0) {
        while (pices[h][w - 1]->type == piceTypeToEnum[typeRand]) {
            typeRand = (int) (rand() % (int) PiceType::_LAST);
        }
    }

    PiceType type = piceTypeToEnum[typeRand];
    pices[h][w] = Game::scenes.at(Util::findScene("game")).loadActor<Pice>(type);
    pices[h][w]->type = type; //TODO: check why object is losing type
    pices[h][w]->piceImg->rect.x = (w * PICE_DIMENSION) + BOARD_MARGIN_LEFT;
    if(y>=0){
        y++;
        pices[h][w]->piceImg->rect.y = ((y * PICE_DIMENSION)*-1) + BOARD_MARGIN_TOP;
    }else    {
        pices[h][w]->piceImg->rect.y = (h * PICE_DIMENSION) + BOARD_MARGIN_TOP;
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


/// Check if sequence is activated
/// \return The socore
int Board::checkInRange(){

    int count_chain = 0;
    bool chain = false;

    PiceType piceType = PiceType::_LAST;

    int score = 0;

    struct struct_found{
        int h;
        int w;
        int chain_size;
        int direction = -1; //1 to go up || 2 to go right
    };
    std::vector<struct_found> found;

    //TODO: optimise these for loops

    //W
    for (int iH = 0; iH < BOARD_H; iH++) {
        for (int iW = 0; iW < BOARD_W; iW++) {
            if(piceType == pices[iH][iW]->type && !pices[iH][iW]->isAnimating()){
                if(count_chain == 0) count_chain++;
                count_chain++;
            } else{
                if(chain){
                    struct_found f;
                    f.h = iH;
                    f.w = iW -1;
                    f.chain_size = count_chain;
                    f.direction = 2;
                    found.push_back(f);
                }
                count_chain=0;
                chain = false;
            }

            if(count_chain == checkRange && !pices[iH][iW]->isAnimating()){
                chain = true;
            }
            piceType = pices[iH][iW]->type;
            if(pices[iH][iW]->isAnimating())piceType = PiceType::_LAST;
        }
        piceType = PiceType::_LAST;
        if(chain){
            struct_found f;
            f.h = iH;
            f.w = BOARD_W -1;
            f.chain_size = count_chain;
            f.direction = 2;
            found.push_back(f);
        }
        chain = false;
        count_chain = 0;
    }

    chain = false;
    count_chain = 0;

    //H
    for (int iW = 0; iW < BOARD_W; iW++) {
        for (int iH = 0; iH < BOARD_H; iH++) {
            if(piceType == pices[iH][iW]->type && !pices[iH][iW]->isAnimating()){
                if(count_chain == 0) count_chain++;
                count_chain++;
            } else{
                if(chain){
                    struct_found f;
                    f.h = iH-1;
                    f.w = iW;
                    f.chain_size = count_chain;
                    f.direction = 1;
                    found.push_back(f);
                }
                count_chain=0;
                chain = false;
            }

            if(count_chain == checkRange && !pices[iH][iW]->isAnimating()){
                chain = true;
            }

            piceType = pices[iH][iW]->type;
            if(pices[iH][iW]->isAnimating())piceType = PiceType::_LAST;
        }
        piceType = PiceType::_LAST;
        if(chain){
            struct_found f;
            f.h = BOARD_H-1;
            f.w = iW;
            f.chain_size = count_chain;
            f.direction = 1;
            found.push_back(f);
        }
        chain = false;
        count_chain = 0;
    }

    while(found.begin() != found.end()){
        struct_found currF= found.back();
        if(currF.direction == 1){
            for (int i = 0; i < currF.chain_size; i++){
                pices[currF.h-i][currF.w]->setDestroy();//-1 because this is not the pice we want
                score ++;
            }
        } else if(currF.direction == 2){
            for (int i = 0; i < currF.chain_size; i++){
                pices[currF.h][currF.w -i]->setDestroy();//-1 because this is not the pice we want
                score ++;
            }
        }

        found.pop_back();
    }

    return score;
}

/// Swap specified pice for the one on top recursivly. If none is on top, a new pice is created
/// \param h height of the pice on the board
/// \param w width of the pice on the board
/// \param Hchain how many blocks where destroyed
/// \param _firstCall internal controller
void Board::smash(unsigned int h, unsigned int w, int Hchain, bool _firstCall){
    if(h >= BOARD_H || w>= BOARD_W){
        std::cout <<"error! pice to smash is out of range"<< std::endl;
        return;
    }
    if(_firstCall)
    {
        if(!pices[h][w]->getDestroy()){
            //TODO: check why this is happening
//            std::cout <<"error! cant smash on pice not marked to destroy"<< std::endl;
            return;
        }
        pices[h][w]->active = false;
    }
    if(h != 0){
        pices[h][w] = pices[h-1][w];
        pices[h][w]->moveDown(1);
        smash(h - 1, w,  Hchain, false);
    }
    else
    {
        genNew(h,w,Hchain);
        pices[h][w]->moveDown(1);
    }


}

int Board::update(){
    Actor::update();

    static int totalScore = 0;
    int initialScore = totalScore;
    int thisUpdateScore = 0;

    int countDestroyH =0;
    bool anyMoving = false;
    int clickedCount = 0;
    bool swap = false;

    static SDL_Point first = {-1,-1};
    static SDL_Point second = {-1,-1};

    for(uint32_t  wInter = 0; wInter < BOARD_W; wInter ++) {
        for (uint32_t  hInter = 0; hInter < BOARD_H; hInter++) {
            //dont mess with moving parts
            if(pices[hInter][wInter]->isAnimating() == true){
                anyMoving = true;
            }
            if(pices[hInter][wInter]->clicked){
                if(first.x != -1){
                    if(
                            ((first.x == wInter +1 || first.x == wInter -1) && first.y == hInter) ||
                            ((first.y == hInter +1 || first.y == hInter -1) && first.x == wInter)
                    ){
                        second.y = hInter;
                        second.x = wInter;
                    } else{//disable click if not near first click
                        pices[first.y][first.x]->clicked = false;
                        pices[hInter][wInter]->clicked = false;
                        clickedCount = 0;
                        first.x = -1;
                        first.y = -1;
                    }
                } else{
                    first.y = hInter;
                    first.x = wInter;
                }
                clickedCount++;
            }
        }
    }

    if(!anyMoving){
        for(uint32_t  wInter = 0; wInter < BOARD_W; wInter ++) {
            int HtoSmash = -1;
            for (uint32_t hInter = 0; hInter < BOARD_H; hInter++) {
                if(pices[hInter][wInter]->isSpining == 2){
                    if(HtoSmash == -1)HtoSmash =hInter;
                    countDestroyH ++;
                }
            }
            if(HtoSmash != -1){
                for(int i = 0; i< countDestroyH; i++){
                    smash(HtoSmash, wInter, i, true);
                }
            }
            countDestroyH = 0;
        }
        // inside if !anyMoving
        if(clickedCount == 2){
            swap = true;

            pices[first.y][first.x]->moveTo((second.x * PICE_DIMENSION) + BOARD_MARGIN_LEFT,
                    (second.y * PICE_DIMENSION) + BOARD_MARGIN_TOP);
            pices[second.y][second.x]->moveTo((first.x * PICE_DIMENSION) + BOARD_MARGIN_LEFT,
                    (first.y * PICE_DIMENSION) + BOARD_MARGIN_TOP);
            pices[first.y][first.x]->clicked = false;
            pices[second.y][second.x]->clicked = false;
            auto temp = pices[first.y][first.x];
            pices[first.y][first.x] = pices[second.y][second.x];
            pices[second.y][second.x] = temp;
        }

        if(!swap){
            //skip checking to wait for move animation on swap
            thisUpdateScore = checkInRange();
            initialScore += thisUpdateScore;
            if(second.x != -1){//if there is a swap going on
                if(thisUpdateScore == 0){
                    //if the swap scores, pice will set to destory and we are good. If not
                    //we check if there was a swap and not on this update. Then we swap back.
                    pices[first.y][first.x]->moveTo((second.x * PICE_DIMENSION) + BOARD_MARGIN_LEFT,
                                                    (second.y * PICE_DIMENSION) + BOARD_MARGIN_TOP);
                    pices[second.y][second.x]->moveTo((first.x * PICE_DIMENSION) + BOARD_MARGIN_LEFT,
                                                      (first.y * PICE_DIMENSION) + BOARD_MARGIN_TOP);
                    auto temp = pices[first.y][first.x];
                    pices[first.y][first.x] = pices[second.y][second.x];
                    pices[second.y][second.x] = temp;

                    first.x =-1;
                    first.y =-1;
                    second.x =-1;
                    second.y =-1;
                } else{
                    first.x =-1;
                    first.y =-1;
                    second.x =-1;
                    second.y =-1;
                }
            }
            else
            {
                //no second to swap, resets first to get ready for new frame check
                first.x =-1;
                first.y =-1;
            }
        }
    }

    if(totalScore < initialScore){
        std::cout << "TOTAL SCORE: " << totalScore << "\n"
                  << " NOW SCORED: " << thisUpdateScore<< std::endl;
        totalScore += thisUpdateScore;
    }

    return 0;
};

int Board::onInput(SDL_Event e){
    Actor::onInput(e);
    return 0;
}