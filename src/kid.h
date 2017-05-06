#ifndef KID_H
#define KID_H

#include "sprite.h"

class Kid : public Sprite {
  public:
    Kid(std::string, int, int, int, int, int, int);

    virtual void update(double);
    virtual void render(sf::RenderTarget&, bool shadered = true);
    virtual void onClick();

};

#endif
