//
// Created by Rato Zumbi on 03/07/2020.
//

#ifndef GAME_PICE_H
#define GAME_PICE_H

#include "../include/Actor.h"
#include "Image.h"

class Pice: public Actor {
    friend class Board;
public:
    bool clicked;
    Image *piceImg;
    Pice();
    ~Pice();
    Pice(std::string);
    void start();
    void start(std::string);
    int update();
    int onInput(SDL_Event);
    void setDestroy();
    bool getDestroy();

    void moveDown();
};


#endif //GAME_PICE_H
