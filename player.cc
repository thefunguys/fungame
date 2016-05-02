#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "world.h"
#include "keymap.h"
#include "sprite.h"
#include "player.h"

#define SQRT2 1.412

Player::Player(std::string fname, SDL_Renderer* renderer, int x, int y, int w, int h, int l) : Sprite::Sprite(fname, renderer, x, y, w, h, l) {
    Bountry tmp(w, l, 5);
    bountry = tmp;
}

void Player::update(double dt) {
    vel = {0, 0};
    if (Keymap::keymap[SDLK_d]) {
        vel.x = speed;
    }
    if (Keymap::keymap[SDLK_a]) {
        vel.x = -speed;
    }
    if (Keymap::keymap[SDLK_w]) {
        vel.y = -speed;
    }
    if (Keymap::keymap[SDLK_s]) {
        vel.y = speed;
    }
    if (vel.x && vel.y) {
        vel.x = vel.x / SQRT2;
        vel.y = vel.y / SQRT2;
    }

    Sprite::update(dt);
}

void Player::render(int vx, int vy) {
    Sprite::render(vx, vy);
}
