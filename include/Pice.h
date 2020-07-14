//
// Created by Rato Zumbi on 03/07/2020.
//

#ifndef GAME_PICE_H
#define GAME_PICE_H

#include "../include/Actor.h"
#include "Image.h"
#include <vector>

class Pice: public Actor {

//TODO: change to class enum (https://stackoverflow.com/questions/2102582/how-can-i-count-the-items-in-an-enum)


    friend class Board;
public:
    bool clicked;
    Image *piceImg;
    Pice(PiceType type);
//    Pice(int type);
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

    const char *getRandomColor();
    const char * colors[5] ={"Color-1.png","Color-2.png","Color-3.png","Color-4.png","Color-5.png"};

    PiceType type;

    //TODO: separate this to a component GameObject Movable
    std::vector<SDL_Point> pointsToMove;
    void moveTo(int x, int y);
    int targetX = 0;
    int targetY = 0;
    int movedownCount = 0;

    bool isAnimating();
    void spin();
private:
    int isMoving = 0;
    int isSpining = 0;
};


#endif //GAME_PICE_H
