#include <iostream>
#include "gameobject.h"
#include "sprite.h"
#include "fns.h"
#include "dialog.h"

const double FRAME_SWITCH = 0.1;

Sprite::Sprite(std::string fname, int x, int y, int w, int h, int cw, int ch) : GameObject::GameObject(fname, x, y, w, h, cw, ch) {
    ss_w = 1;
    ss_h = 1;
    frame_t = 0.0;
    curframe_x = 0;
    curframe_y = 0;
    speed = 100.0;
}

void Sprite::update(double dt) {
    frame_t += dt;
    if (frame_t > FRAME_SWITCH) {
        if (++curframe_x >= ss_w) {
            curframe_x = 0;
        }
        frame_t = 0;
    }
    if (close_to_zero(vel.x) && close_to_zero(vel.y)) {
        curframe_x = 0;
    }
    GameObject::update(dt);
    switch (direction) {
    case 0:
        if (ss_h > 2) {
            curframe_y = 1;
        }
        break;
    case 1:
    case 2:
    case 3:
        curframe_y = 0;
        break;
    case 4:
        if (ss_h > 3) {
            curframe_y = 2;
        }
        break;
    default:
        if (ss_h > 1) {
            curframe_y = 3;
        }
        break;
    }
    if (focused && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        onClick();
    }
}

void Sprite::render(sf::RenderTarget& window, bool shadered) {
    sprite.setTextureRect(sf::IntRect(curframe_x * w, curframe_y * h, w, h));
    GameObject::render(window, shadered);
}

void Sprite::onClick() {
    Dialog::setDialog("it's a " + name);
}
