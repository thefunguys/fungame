#include <iostream>
#include <cmath>
#include "world.h"
#include "keymap.h"
#include "sprite.h"
#include "player.h"
#include "shadermanager.h"
#include "dialog.h"

#define SQRT2 1.412
#define keydown(key) sf::Keyboard::isKeyPressed(sf::Keyboard::key)


Player::Player(std::string fname, int x, int y, int w, int h, int cw, int ch) : Sprite::Sprite(fname, x, y, w, h, cw, ch) {

    shader = ShaderManager::instance()->pShader;
}

void Player::update(double dt) {
    vel = {0, 0};
    if (keydown(D) || keydown(E) || keydown(C)) {
        vel.x = speed;
    }
    if (keydown(A) || keydown(Q) || keydown(Z)) {
        vel.x = -speed;
    }
    if (keydown(W) || keydown(E) || keydown(Q)) {
        vel.y = -speed;
    }
    if (keydown(Z) || keydown(X) || keydown(C) || keydown(S)) {
        vel.y = speed;
    }

    if (vel.x && vel.y) {
        vel.x = vel.x / SQRT2;
        vel.y = vel.y / SQRT2;
    }
    if (sf::Joystick::isConnected(0) && sf::Joystick::hasAxis(0, sf::Joystick::Z)) {
        vel = { sf::Joystick::getAxisPosition(0, sf::Joystick::X),
                sf::Joystick::getAxisPosition(0, sf::Joystick::Y)
              };
    }

    Sprite::update(dt);
}

void Player::render(sf::RenderWindow& window, bool shadered) {
    Sprite::render(window, shadered);
}
