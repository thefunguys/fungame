#include <math.h>
#include "rat.h"
#include "game.h"

Rat::Rat(std::string fname, int x, int y, int w, int h, int cw, int ch) : 
  Sprite::Sprite(fname, x, y, w, h, cw, ch) {
    }

void Rat::update(double dt) {
    double dx = Game::p->pos.x - pos.x;
    double dy = Game::p->pos.y - pos.y;
    vel.x = 20.0 * dx / (fabs(dx) + 1);
    vel.y = 20.0 * dy / (fabs(dy) + 1);
    Sprite::update(dt);
}

void Rat::render(sf::RenderWindow& window, bool shadered) {
    Sprite::render(window, shadered);
}
