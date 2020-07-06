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

    Image *loadImage(string);
    Image *loadImage(string, SDL_Renderer &);
    Image *loadImage(string, SDL_Renderer &, int, int);
    Image *loadImage(string, SDL_Renderer &, int, int, bool);

//    //TODO: use this
//    void loadActor(Pice *act, std::string name){
//        act->start(name);
//
//        actors.push_back(act);
//    }
//
//    //TODO: use this
//    void loadActor(Pice *act, Image* img){
//        act->start(img);
//
//        actors.push_back(act);
//    }

    //TODO: use templates and vardic to load actors
    template <class T> auto loadActor(){
        auto *newActor = new T();
        newActor->start();

        actors.push_back(newActor);
        return newActor;
    }

    template <class T> T loadActor(std::string name){
        auto *newActor = new T();
        newActor->start(name);

        actors.push_back(newActor);
        return *newActor;
    }
    template <class T> T loadActor(std::string name, int x, int y){
        auto *newActor = new T();
        newActor->start(name,x,y);

        actors.push_back(newActor);
        return *newActor;
    }

//    template <class T> void loadActor(...){
//        va_list vl;
//        auto *newActor = new T();
//        if(typeid(T) == typeid(Pice)){
//            va_start(vl,1);
//            newActor->start(va_arg(vl,std::string));
//        }
//
//        actors.push_back(newActor);
//        va_end(vl);
//    }

    int GetImagesSize();
    int GetActorsSize();

    Image *GetImage(int);
    Image *GetImage(string);
    Actor *GetActor(int);

    Scene();
    Scene(std::string);
    ~Scene();

//private:
    std::vector<Image*> images;
    std::vector<Actor*> actors;

};


#endif //SDL_SNAKE_SCENE_H
