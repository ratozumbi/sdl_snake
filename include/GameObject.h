//
// Created by ratozumbi on 6/23/20.
//

#ifndef SDL_SNAKE_GAMEOBJECT_H
#define SDL_SNAKE_GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <string>
using std::string;
#include <SDL2/SDL_image.h>

class GameObject
{
public:
    bool active = true;
    string name;
    SDL_Rect rect;
    GameObject (string , SDL_Rect &);
    GameObject (SDL_Rect &);
    GameObject ();


};

#endif //SDL_SNAKE_GAMEOBJECT_H
