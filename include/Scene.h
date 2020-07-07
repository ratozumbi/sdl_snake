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
    Image *loadImage(string, int, int);
    Image *loadImage(string, int, int, bool);

    /// Loads an actor
    /// \tparam T The class type derived from Actor
    template <class T> void loadActor(){
        actors.push_back(new T());
    }

    /// Loads an actor
    /// \tparam T The class type derived from Actor
    /// \param str Any string parameter to be passed to the constructor
    template <class T> void loadActor(std::string str){
        actors.push_back(new T(str));
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
