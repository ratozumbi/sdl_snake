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

    /// Push a new actor for the game
    /// \tparam T An Actor derived class type
    /// \return Pointer to the new Actor
    template <class T> T* loadActor(){
        auto ret = new T();
        actors.push_back(ret);
        return ret;
    }

    /// Loads an actor
    /// \tparam T The class type derived from Actor
    /// \param str Any string parameter to be passed to the constructor
    /// \return Pointer to the new Actor
    template <class T> T* loadActor(std::string str){
        auto ret = new T(str);
        actors.push_back(ret);
        return ret;
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
