#ifndef SPRITE_H
#define SPRITE_H

#include "gameobject.h"

class Sprite : public GameObject {
public:
    Sprite(std::string, SDL_Renderer*, int, int, int, int);
    int hp;
    int stats;
    std::string name;
    virtual void update(double);
};

#endif
