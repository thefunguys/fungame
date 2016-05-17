#include <iostream>
#include <cmath>
#include "world.h"
#include "keymap.h"
#include "sprite.h"
#include "player.h"

#define SQRT2 1.412

Player::Player(std::string fname, int x, int y, int w, int h, int l) : Sprite::Sprite(fname, x, y, w, h, l) {
    Bountry tmp(w, l, 5);
    bountry = tmp;
}

void Player::update(double dt) {
    vel = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        vel.x = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        vel.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        vel.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        vel.y = speed;
    }
    if (vel.x && vel.y) {
        vel.x = vel.x / SQRT2;
        vel.y = vel.y / SQRT2;
    }

    Sprite::update(dt);
}

void Player::render(sf::RenderWindow& window, int vx, int vy) {
    Sprite::render(window, vx, vy);
}
