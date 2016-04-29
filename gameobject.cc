#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "game.h"
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
    base_x_offset = 0.0;
    base_y_offset = h * 0.5;
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
    dst_r.w = w;
    dst_r.h = h;

    SDL_RenderCopy(renderer, texture, &src_r, &dst_r);
}

double GameObject::cx() {
    return x + base_x_offset;
}

double GameObject::cy() {
    return y + base_y_offset;
}

bool GameObject::collide(double mx, double my, GameObject* other) {
    return ((cx() + mx < other->x + other->w) && (x + mx + w > other->cx())) 
        && ((cy() + my < other->y + other->h) && (y + my + h > other->cy()));
}

void GameObject::update(double dt) {
    double mx = dx * dt;
    double my = dy * dt;
    if (fabs(mx) > 0.005 || fabs(my) > 0.005) {
        for (GameObject* ogo : Game::current_world->gobjs) {
            if (ogo != this) {
                if (collide(mx, 0.0, ogo)) {
                    mx = 0;
                }
                if (collide(0.0, my, ogo))
                    my = 0;
            }
        }
    }
    x += mx;
    y += my;
}
