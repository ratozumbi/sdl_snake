//
// Created by ratozumbi on 6/26/20.
//

#ifndef ENJOIADO_SCENE_H
#define ENJOIADO_SCENE_H


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

    /// Loads an actor
    /// \tparam T The class type derived from Actor
    /// \param i Any int parameter to be passed to the constructor
    /// \return Pointer to the new Actor
    template <class T> T* loadActor(int i){
        auto ret = new T(i);
        actors.push_back(ret);
        return ret;
    }

    /// Loads an actor
    /// \tparam T The class type derived from Actor
    /// \param i Any PiceType parameter to be passed to the constructor
    /// \return Pointer to the new Actor
    //TODO: this is getting rediculous
    template <class T> T* loadActor(PiceType type){
        auto ret = new T(type);
        actors.push_back(ret);
        return ret;
    }

    //TODO: think a better way to pass parameters to constructors so the system is more scalable


    int GetImagesSize();
    int GetActorsSize();

    Image *GetImage(int);
    Image *getImage(string);
    Actor *getActor(int);
    void deleteActor(Actor *);
    void deleteActor(int);
    void deleteImage(Image *);
    void deleteImage(int);

    int update();

    Scene();
    Scene(std::string);
    ~Scene();

    void deleteActors();

    void deleteImages();

private:
    std::vector<Image*> images;
    std::vector<Actor*> actors;

};


#endif //ENJOIADO_SCENE_H
