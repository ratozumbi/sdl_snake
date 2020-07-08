//
// Created by Rato Zumbi on 07/07/2020.
//

#include "../include/Board.h"
#include "../include/Game.h"

char * getRandomColor(){
    char * colors[]= {"Color-1.png","Color-2.png","Color-3.png","Color-4.png","Color-5.png"};
    return colors[rand() % 5];
}

Board::Board():Actor() {

    for(int wInter = 0; wInter < BOARD_W; wInter ++){
        for(int hInter = 0; hInter < BOARD_W; hInter ++){
            auto a = Game::scenes.at(Util::findScene("game")).loadActor<Pice>(getRandomColor());
            pices[hInter][wInter] = dynamic_cast<Pice*>(a);
            pices[hInter][wInter]->piceImg->rect.x = (wInter * 70) + 200;//TODO: make positions scalable
            pices[hInter][wInter]->piceImg->rect.y = (hInter * 70) + 100;
            pices[hInter][wInter]->piceImg->active = true;
        }
    }
};
Board::~Board(){

}

void Board::start() {
};

int Board::update(){
    Actor::update();

    for(int wInter = 0; wInter < BOARD_W; wInter ++) {
        for (int hInter = 0; hInter < BOARD_H; hInter++) {
            //check if any piceImg needs to be destroyed
            if(pices[hInter][wInter] && pices[hInter][wInter]->getDestroy()){
                Game::scenes.at(1).deleteActor(pices[wInter][hInter]);
                pices[hInter][wInter] = nullptr;
                for (int hInterMove = hInter-1; hInterMove >= 0; hInterMove--) {
                    pices[hInterMove][wInter]->moveDown();
                }
            }
        }
    }

    return 0;
};

int Board::onInput(SDL_Event e){
    Actor::onInput(e);
    return 0;
}