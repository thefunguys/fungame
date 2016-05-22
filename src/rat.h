#ifndef RAT_H
#define RAT_H

#include "sprite.h"

class Rat : public Sprite {
  public:
    Rat(std::string, int, int, int, int, int);
    virtual void update(double);
    virtual void render(sf::RenderWindow&, bool shadered = true);
    virtual void onClick();
};

#endif
