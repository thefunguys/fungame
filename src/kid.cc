#include <math.h>
#include <stdio.h>
#include "dialog.h"
#include "kid.h"
#include "fns.h"
#include "game.h"

Kid::Kid(std::string fname, int x, int y, int w, int h, int cw, int ch) :
    Sprite::Sprite(fname, x, y, w, h, cw, ch) {
    shadowcasts = false;
}

void Kid::update(double dt) {
    double dx = Game::p->pos.x + Game::p->w / 2 - (pos.x + w / 2);
    double dy = Game::p->pos.y + Game::p->h - (pos.y + h / 2);
    rotation = atan(dy / dx) * RADDEG + 90;
    if (fabs(dx) > 5.0 || fabs(dy) > 5.0) {
        vel.x = 20.0 * dx / (fabs(dx) + 1);
        vel.y = 20.0 * dy / (fabs(dy) + 1);
    } else {
        vel.x = 0;
        vel.y = 0;
    }
    Sprite::update(dt);
}

void Kid::render(sf::RenderTarget& window, bool shadered) {
    Sprite::render(window, shadered);
}

void Kid::onClick() {
    Dialog::setDialog("it's your trusty pet rat");
}
