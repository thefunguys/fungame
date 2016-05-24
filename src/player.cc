#include <iostream>
#include <cmath>
#include "world.h"
#include "keymap.h"
#include "sprite.h"
#include "player.h"
#include "shadermanager.h"
#include "dialog.h"

#define SQRT2 1.412

Player::Player(std::string fname, int x, int y, int w, int h, int l) : Sprite::Sprite(fname, x, y, w, h, l) {
    shader = ShaderManager::instance()->pShader;
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
    if (sf::Joystick::isConnected(0) && sf::Joystick::hasAxis(0, sf::Joystick::Z)) {
        vel = { sf::Joystick::getAxisPosition(0, sf::Joystick::X),
                sf::Joystick::getAxisPosition(0, sf::Joystick::Y)};
    }

    Sprite::update(dt);
}

void Player::render(sf::RenderWindow& window, bool shadered) {
    Sprite::render(window, shadered);
}
