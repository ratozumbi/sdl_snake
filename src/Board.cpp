//
// Created by Rato Zumbi on 06/07/2020.
//

#include "../include/Board.h"
#include "../include/Pice.h"
#include "../include/Game.h"

Pice* pices[BOARD_H][BOARD_W];

Board::Board(): Actor(){

}
void Board::start(){

    for(int hIter = 0; hIter < BOARD_H; hIter++){
        for(int wIter = 0; wIter < BOARD_W; wIter++){
            pices[hIter][wIter] = Game::scenes.at(1).loadActor<Pice>();//70x70
        }
    }
}
int Board::update(){
    Actor::update();
    return 0;
}
int Board::onInput(SDL_Event e){
    Actor::onInput(e);
    return 0;
}

