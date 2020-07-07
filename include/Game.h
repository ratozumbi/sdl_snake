//
// Created by ratozumbi on 6/24/20.
//

#ifndef SDL_SNAKE_GAME_H
#define SDL_SNAKE_GAME_H

#include <vector>
#include "GameObject.h"

#include "../include/Image.h"
#include "../include/Arrow.h"
#include "Scene.h"

namespace Engine {
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
}
namespace Game {
    extern std::vector<Scene> scenes;
    extern unsigned int currentScene;
}
namespace Util {
    unsigned int findScene(std::string );
    Image *findImage(std::string );
}

#endif //SDL_SNAKE_GAME_H
