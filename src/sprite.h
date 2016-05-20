#ifndef SPRITE_H
#define SPRITE_H

#include "gameobject.h"

class Sprite : public GameObject {
  public:
    Sprite(std::string, int, int, int, int, int);

    // spritesheet width and height
    int ss_w;
    int ss_h;

    // current frame in the spritesheet
    int curframe_x;
    int curframe_y;

    // character specific parameters
    int hp;
    int stats;
    double speed;
    std::string name;


    // change current sheet every frame_t seconds
    double frame_t;

    virtual void update(double);
    virtual void render(sf::RenderWindow&, bool shadered = true);
};

#endif
