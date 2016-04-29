#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"

class Player : public GameObject {
public:
    Player(std::string, SDL_Renderer*, int, int, int , int);
    void update(double);
};

#endif
