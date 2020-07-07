//
// Created by ratozumbi on 6/25/20.
//

#include "../include/Scene.h"
#include "../include/Game.h"

unsigned int Game::currentScene;
std::vector<Scene> Game::scenes;
SDL_Window *Engine::window;
SDL_Renderer *Engine::renderer;

unsigned int Util::findScene(char* name){
    for (unsigned int iScene = 0; iScene < Game::scenes.size(); iScene++){
        if(std::strcmp(Game::scenes.at(iScene).name,name) == 0){
            return iScene;
        }
    }
    //TODO: throw not found
	return 666;
}

/// Finds an image in any scene
/// \param name The name of the image to search
/// \return returns an Image* or NULL if not found
Image *Util::findImage(char * name){
    for(unsigned int iScene = 0; iScene < Game::scenes.size(); iScene++){
        int imgs = Game::scenes.at(iScene).GetImagesSize();
        for(int iImage = 0; iImage < imgs; iImage++){
            if(std::strcmp(Game::scenes.at(iScene).GetImage(iImage)->name, name) == 0){
                return Game::scenes.at(iScene).GetImage(iImage);
            }
        }
    }
	return NULL;
}