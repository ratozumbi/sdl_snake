//
// Created by Rato Zumbi on 03/07/2020.
//

#ifndef GAME_PICE_H
#define GAME_PICE_H

#include "../include/Actor.h"
#include "Image.h"

enum class PiceType{
    P_BLACK
};

class Pice: public Actor {

public:
    bool clicked;
    Image *pice;
    Pice();
    ~Pice();
    void start();
    void start(char *);
    void start(char *, int , int);
    void start(Image *);
    int update();
    int onInput(SDL_Event);

};


#endif //GAME_PICE_H
