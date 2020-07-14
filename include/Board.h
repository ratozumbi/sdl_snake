//
// Created by Rato Zumbi on 07/07/2020.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#define BOARD_W 8
#define BOARD_H 8
#define PICE_DIMENSION 70

#include "Actor.h"
#include "Pice.h"


class Board : public Actor{

public:
    Board();
    ~Board();
    Pice *pices[BOARD_H][BOARD_W];
    void start();
    int update();
    int onInput(SDL_Event);

    int checkInRange();
    void genNew(uint32_t h, uint32_t w,int y=-1);
    void smash(unsigned int h, unsigned int w, bool _firstCall = true, int Hchain=0);

private:
    const int checkRange = 3;
};



#endif //GAME_BOARD_H
