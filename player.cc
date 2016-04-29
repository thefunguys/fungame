#include <SDL2/SDL.h>
#include "keymap.h"
#include "sprite.h"
#include "gameobject.h"
#include "player.h"

Player::Player(std::string fname, SDL_Renderer* renderer, int x, int y, int w, int h) : GameObject::GameObject(fname, renderer, x, y, w, h) {
}

void Player::update(double dt) {
    if (keymap[SDLK_w]) {
        dx = 20;
    }
    if (keymap[SDLK_a]) {
        dx = -20;
    }
    GameObject::update(dt);
}
