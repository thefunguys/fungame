#ifndef SPRITE_H
#define SPRITE_H

#include "gameobject.h"

class Sprite : public GameObject {
public:
    Sprite(std::string, SDL_Renderer*, int, int, int, int);
    int ss_w;
    int ss_h;
    int curframe_x;
    int curframe_y;
    int hp;
    int stats;

    double frame_t;
    double speed;
    std::string name;
    virtual void update(double);
    virtual void render(SDL_Renderer*, int, int);
};

#endif
