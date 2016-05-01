#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

class Player : public Sprite {
public:
    Player(std::string, SDL_Renderer*, int, int, int , int, int);
    virtual void update(double);
    virtual void render(SDL_Renderer*, int, int);
};

#endif
