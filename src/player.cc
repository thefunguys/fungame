#include <iostream>
#include <cmath>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include "world.h"
#include "keymap.h"
#include "sprite.h"
#include "player.h"
#include "shadermanager.h"
#include "dialog.h"
#include "game.h"

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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        auto wind = Game::cur_window;
        auto mpos = sf::Mouse::getPosition(*wind);
        auto gmpos = gpos(*wind, mpos.x, mpos.y);
        auto diffv = glm::vec2(gmpos.x - (pos.x + 16), gmpos.y - (pos.y + 16));
        auto diffvn = glm::normalize(diffv);
        vel.x = diffvn.x * speed;
        vel.y = diffvn.y * speed;
    }

    Sprite::update(dt);
}

void Player::render(sf::RenderTarget& window, bool shadered) {
    Sprite::render(window, shadered);
}
