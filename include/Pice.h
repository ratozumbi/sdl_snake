//
// Created by Rato Zumbi on 03/07/2020.
//

#ifndef ENJOIADO_PICE_H
#define ENJOIADO_PICE_H

#include "../include/Actor.h"
#include "Image.h"
#include <vector>
#define PICE_DIMENSION 70

class Pice: public Actor {

    friend class Board;
public:
    bool clicked = false;
    bool drag = false;

    Image *piceImg;
    Pice(PiceType type);
    Pice();
    ~Pice();
    Pice(std::string);
    void start();
    void start(std::string);
    int update();
    int onInput(SDL_Event);
    void setDestroy();
    bool getDestroy();

    void moveDown(int squares = 1);

    const char * colors[5] ={"Color-1.png","Color-2.png","Color-3.png","Color-4.png","Color-5.png"};

    PiceType type;

    //TODO: separate this to a component GameObject Movable
    std::vector<SDL_Point> pointsToMove;
    void moveTo(int x, int y);

    bool isAnimating();
    void spin();
private:
    bool isMoving = false;
    int isSpining = 0;
};


#endif //ENJOIADO_PICE_H
