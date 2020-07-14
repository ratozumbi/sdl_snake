//
// Created by ratozumbi on 6/23/20.
//

#ifndef ENJOIADO_GAMEOBJECT_H
#define ENJOIADO_GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using std::string;

class GameObject
{
public:
    bool active = true;
    string name;
    SDL_Rect rect;//TODO: Refactor rect to Image
    GameObject (string , SDL_Rect &);
    GameObject ();
    ~GameObject ();
};

#endif //ENJOIADO_GAMEOBJECT_H
