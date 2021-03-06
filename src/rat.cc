#include <math.h>
#include <stdio.h>
#include "dialog.h"
#include "rat.h"
#include "game.h"

Rat::Rat(std::string fname, int x, int y, int w, int h, int cw, int ch) :
    Sprite::Sprite(fname, x, y, w, h, cw, ch) {
    shadowcasts = false;
}

void Rat::update(double dt) {
    double dx = Game::p->pos.x + Game::p->w / 2 - (pos.x + w / 2);
    double dy = Game::p->pos.y + Game::p->h - (pos.y + h / 2);
    if (fabs(dx) > 20.0 || fabs(dy) > 20.0) {
        vel.x = 20.0 * dx / (fabs(dx) + 1);
        vel.y = 20.0 * dy / (fabs(dy) + 1);
    } else {
        vel.x = 0;
        vel.y = 0;
    }
    Sprite::update(dt);
}

void Rat::render(sf::RenderTarget& window, bool shadered) {
    Sprite::render(window, shadered);
}

void Rat::onClick() {
    Dialog::setDialog("it's your trusty pet rat");
}
