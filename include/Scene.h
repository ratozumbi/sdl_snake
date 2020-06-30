//
// Created by ratozumbi on 6/26/20.
//

#ifndef SDL_SNAKE_SCENE_H
#define SDL_SNAKE_SCENE_H


#include <vector>
#include "GameObject.h"
#include "Actor.h"
#include "Image.h"

class Scene{

public:
    std::string name;


    Image *loadImage(string, SDL_Renderer &);
    Image *loadImage(string, SDL_Renderer &, int, int);
    Image *loadImage(string, SDL_Renderer &, int, int, bool);

    template <class T> void loadActor(){
        T *newActor = new T();
        newActor->start();

        actors.push_back(newActor);
    }

    int GetImagesSize();
    int GetActorsSize();

    Image *GetImage(int);
    Actor *GetActor(int);

    Scene();
    Scene(std::string);
    ~Scene();

private:
    std::vector<Image*> images;
    std::vector<Actor*> actors;

};


#endif //SDL_SNAKE_SCENE_H
