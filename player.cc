#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "world.h"
#include "keymap.h"
#include "sprite.h"
#include "player.h"

#define SQRT2 1.412

Player::Player(std::string fname, SDL_Renderer* renderer, int x, int y, int w, int h) : Sprite::Sprite(fname, renderer, x, y, w, h) {
    base_x_offset = 0.4 * w;
    pw = 0.2 * w;
    base_y_offset = 0.9 * h;
    ph = 0.1 * h;
    World::cur_player = this;
}

void Player::update(double dt) {
    dx = dy = 0;
    if (Keymap::keymap[SDLK_d]) {
        dx = speed;
    }
    if (Keymap::keymap[SDLK_a]) {
        dx = -speed;
    }
    if (Keymap::keymap[SDLK_w]) {
        dy = -speed;
    }
    if (Keymap::keymap[SDLK_s]) {
        dy = speed;
    }
    if (dx && dy) {
        dx = dx / SQRT2;
        dy = dy / SQRT2;
    }

    Sprite::update(dt);
}

void Player::render(SDL_Renderer* renderer, int vx, int vy) {
    Sprite::render(renderer, vx, vy);
}
