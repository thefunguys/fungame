#include <SDL2/SDL.h>
#include <iostream>
#include "gameobject.h"
#include "sprite.h"

const double FRAME_SWITCH = 0.3;

Sprite::Sprite(std::string fname, SDL_Renderer* r, int x, int y, int w, int h) : GameObject::GameObject(fname, r, x, y, w, h) {
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
        if (++curframe_x >= ss_w)
            curframe_x = ss_w;
        frame_t = 0;
        std::cout << "frame_t trigger" << std::endl;
    }
    GameObject::update(dt);
}

void Sprite::render(SDL_Renderer* renderer, int vx, int vy) {
    SDL_Rect src_r;
    SDL_Rect dst_r;

    src_r.x = curframe_x * w;
    src_r.y = curframe_y * h;
    src_r.w = w;
    src_r.h = h;

    dst_r.x  = vx + (int) x;
    dst_r.y = vy + (int) y;
    dst_r.w = w;
    dst_r.h = h;

    SDL_RenderCopyEx(renderer, texture, &src_r, &dst_r, 0.0, NULL, 
            direction > 4 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
