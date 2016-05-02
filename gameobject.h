#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <map>
#include "bountry.h"
#include "LTexture.h"

class GameObject {
  public:
    LTexture texture;
    std::map<std::string, SDL_Rect> surface_map;
    /*   7 0 1
     *  6     2
     *   5 4 3 */
    int direction;
    pVector pos;
    // where we start to count for collisions
    Bountry bountry;

    pVector vel;
    int w, h, l;

    // pw and ph represent the width and height of objects in the collision system

    double mass;

    // cx and cy calculate n + base_n_offset


    virtual void render(int, int);
    virtual void update(double dt);
    //bool collide(double, double, GameObject*);

    GameObject(std::string, SDL_Renderer*, int, int, int, int, int);
};

#endif
