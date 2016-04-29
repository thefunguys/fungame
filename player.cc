#include <iostream>
#include <SDL2/SDL.h>
#include "keymap.h"
#include "sprite.h"
#include "player.h"

Player::Player(std::string fname, SDL_Renderer* renderer, int x, int y, int w, int h) : Sprite::Sprite(fname, renderer, x, y, w, h) {
}

void Player::update(double dt) {
    dx = dy = 0;
    if (Keymap::keymap[SDLK_d]) {
        dx = 50;
    }
    if (Keymap::keymap[SDLK_a]) {
        dx = -50;
    }
    if (Keymap::keymap[SDLK_w]) {
        dy = -50;
    }
    if (Keymap::keymap[SDLK_s]) {
        dy = 50;
    }
    Sprite::update(dt);
}
