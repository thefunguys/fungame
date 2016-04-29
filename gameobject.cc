#include <iostream>
#include <SDL2/SDL.h>
#include "gameobject.h"

GameObject::GameObject(std::string fname, SDL_Renderer* renderer, 
        int nx, int ny, int nw, int nh) {
    SDL_Surface* surface = SDL_LoadBMP(fname.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    x = nx;
    y = ny; 
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

    dst_r.x = x;
    dst_r.y = y;
    dst_r.w = w;
    dst_r.h = h;

    SDL_RenderCopy(renderer, texture, &src_r, &dst_r);
}

void GameObject::update(double dt) {

}
