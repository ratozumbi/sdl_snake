//
// Created by ratozumbi on 6/25/20.
//

#include "../include/Scene.h"
#include "../include/Game.h"

unsigned int Game::currentScene;
std::vector<Scene> Game::scenes;

unsigned int Util::findScene(std::string name){
    for (unsigned int iScene = 0; iScene < Game::scenes.size(); iScene++){
        if(Game::scenes.at(iScene).name.compare(name) == 0){
            return iScene;
        }
    }
    //TODO: throw not found
}

Image *Util::findImage(std::string name){
    for(int iScene = 0; iScene < Game::scenes.size(); iScene++){
        int imgs = Game::scenes.at(iScene).GetImagesSize();
        for(int iImage = 0; iImage < imgs; iImage++){
            if(Game::scenes.at(iScene).GetImage(iImage)->name.compare(name) == 0){
                return Game::scenes.at(iScene).GetImage(iImage);
            }
        }
    }
    //TODO: throw not found
}