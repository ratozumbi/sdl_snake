//
// Created by ratozumbi on 6/23/20.
//

#ifndef SDL_SNAKE_GAMEOBJECT_H
#define SDL_SNAKE_GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class GameObject
{
public:
    bool active = true;
    char* name;
    SDL_Rect rect;//TODO: Refactor rect to Image
    GameObject (char* , SDL_Rect &);
    GameObject (SDL_Rect &);
    GameObject ();
    ~GameObject ();
};

#endif //SDL_SNAKE_GAMEOBJECT_H
