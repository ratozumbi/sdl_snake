//
// Created by ratozumbi on 6/24/20.
//

#ifndef ENJOIADO_GAME_H
#define ENJOIADO_GAME_H


#include <vector>
#include "GameObject.h"

#include "../include/Image.h"
#include "../include/Arrow.h"
#include "Scene.h"

namespace Engine {
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
    const int targetFPS = 120;
    const int frameDelay = 1000 / targetFPS;
    extern Uint32 dragEventType;
}
namespace Game {
    extern std::vector<Scene> scenes;
    extern unsigned int currentScene;
}
namespace Util {
    unsigned int findScene(std::string );
    Image *findImage(std::string );
    double lerp(float,float,float);
}

#endif //ENJOIADO_GAME_H
