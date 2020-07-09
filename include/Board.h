//
// Created by Rato Zumbi on 07/07/2020.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#define BOARD_W 8
#define BOARD_H 8

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

    void genNew(int h, int w);
    void swapUp(unsigned int h, unsigned int w, bool _firstCall);
};



#endif //GAME_BOARD_H
