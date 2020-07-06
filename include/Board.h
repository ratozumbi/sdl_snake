//
// Created by Rato Zumbi on 06/07/2020.
//

#ifndef SDL_SNAKE_BOARD_H
#define SDL_SNAKE_BOARD_H

#include "Pice.h"
#include "Actor.h"

#define BOARD_W 8
#define BOARD_H 8

class Board: public Actor {
public:
    Pice* pices[BOARD_H][BOARD_W];
    Board();
    ~Board();
    void start();
    int update();
    int onInput(SDL_Event);

};


#endif //GAME_BOARD_H
