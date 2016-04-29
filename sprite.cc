#include <SDL2/SDL.h>
#include "gameobject.h"
#include "sprite.h"

Sprite::Sprite(std::string fname, SDL_Renderer* r, int x, int y, int w, int h) : GameObject::GameObject(fname, r, x, y, w, h) {
}

void Sprite::update(double dt) {
    GameObject::update(dt);
}
