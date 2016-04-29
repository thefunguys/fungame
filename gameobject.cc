#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "gameobject.h"

GameObject::GameObject(std::string fname, SDL_Renderer* renderer, 
        int nx, int ny, int nw, int nh) {
    SDL_Surface* surface = IMG_Load(fname.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    x = (double) nx;
    y = (double) ny; 
    dx = 0.0;
    dy = 0.0;
    w = nw;
    h = nh;
    mass = 1.0;
}

void GameObject::render(SDL_Renderer* renderer) {
    SDL_Rect src_r;
    SDL_Rect dst_r;

    src_r.x = 0;
    src_r.y = 0;
    src_r.w = w;
    src_r.h = h;

    dst_r.x = (int) x;
    dst_r.y = (int) y;
    dst_r.w = w * 2;
    dst_r.h = h * 2;

    SDL_RenderCopy(renderer, texture, &src_r, &dst_r);
}

void GameObject::update(double dt) {
    x += dx * dt;
    y += dy * dt;
}
