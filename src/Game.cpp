//
// Created by ratozumbi on 6/25/20.
//

#include "../include/Scene.h"
#include "../include/Game.h"

unsigned int Game::currentScene;
std::vector<Scene> Game::scenes;
SDL_Window *Engine::window;
SDL_Renderer *Engine::renderer;

unsigned int Util::findScene(std::string name){
    for (unsigned int iScene = 0; iScene < Game::scenes.size(); iScene++){
        if(Game::scenes.at(iScene).name.compare(name) == 0){
            return iScene;
        }
    }
    //TODO: throw not found
	return 666;
}

/// Finds an image in any scene
/// \param name The name of the image to search
/// \return returns an Image* or NULL if not found
Image *Util::findImage(std::string name){
    for(unsigned int iScene = 0; iScene < Game::scenes.size(); iScene++){
        int imgs = Game::scenes.at(iScene).GetImagesSize();
        for(int iImage = 0; iImage < imgs; iImage++){
            if(Game::scenes.at(iScene).GetImage(iImage)->name.compare(name) == 0){
                return Game::scenes.at(iScene).GetImage(iImage);
            }
        }
    }
	return NULL;
}

//TODO: safe convert to int
double Util::lerp(float a, float b, float f)
{
    return a + f * (b - a);
}