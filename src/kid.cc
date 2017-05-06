#include <math.h>
#include <stdio.h>
#include "dialog.h"
#include "kid.h"
#include "fns.h"
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include "game.h"

Kid::Kid(std::string fname, int x, int y, int w, int h, int cw, int ch) :
    Sprite::Sprite(fname, x, y, w, h, cw, ch) {
    shadowcasts = false;
}

void Kid::update(double dt) {
    double dx = Game::p->pos.x + Game::p->w / 2 - (pos.x + w / 2);
    double dy = Game::p->pos.y + Game::p->h / 2 - (pos.y + h / 2);
    auto dvec = glm::vec2(dx, dy);
    auto dvecnorm = glm::normalize(dvec);
    rotation = atan(dy / dx) * RADDEG + 90;
    if (fabs(dx) > 10.0 || fabs(dy) > 10.0) {
        vel.x = 20.0 * dvecnorm.x;
        vel.y = 20.0 * dvecnorm.y;
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
