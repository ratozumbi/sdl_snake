//
// Created by ratozumbi on 6/26/20.
//

#ifndef SDL_SNAKE_SCENE_H
#define SDL_SNAKE_SCENE_H


#include <vector>
#include "GameObject.h"
#include "Actor.h"
#include "Image.h"
#include "Pice.h"

class Scene{

public:
    std::string name;


    Image *loadImage(string, SDL_Renderer &);
    Image *loadImage(string, SDL_Renderer &, int, int);
    Image *loadImage(string, SDL_Renderer &, int, int, bool);

    void loadActor(Pice *act, std::string name){
        act->start(name);

        actors.push_back(act);
    }

    void loadActor(Pice *act, Image* img){
        act->start(img);

        actors.push_back(act);
    }

    //TODO: use templates to load actors
    template <class T> void loadActor(){
        actors.push_back(new T());
    }

    template <class T> void loadActor(std::string name){
        T *newActor = new T();
        newActor->start(name);

        actors.push_back(newActor);
    }

    int GetImagesSize();
    int GetActorsSize();

    Image *GetImage(int);
    Image *GetImage(string);
    Actor *GetActor(int);

    Scene();
    Scene(std::string);
    ~Scene();

private:
    std::vector<Image*> images;
    std::vector<Actor*> actors;

};


#endif //SDL_SNAKE_SCENE_H
