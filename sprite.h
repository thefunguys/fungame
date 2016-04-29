#ifndef SPRITE_H
#define SPRITE_H

#include "gameobject.h"

class Sprite : public GameObject {
    int hp;
    int stats;
    std::string name;
};

#endif
