#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "game.h"
#include "gameobject.h"
#include "fns.h"

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
    pw = w;
    ph = 0.3 * h;
    base_x_offset = 0.0;
    direction = 2;
    base_y_offset = h * 0.7;
    mass = 1.0;
}

void GameObject::render(SDL_Renderer* renderer, int vx, int vy) {
    SDL_Rect src_r;
    SDL_Rect dst_r;

    src_r.x = 0;
    src_r.y = 0;
    src_r.w = w;
    src_r.h = h;

    // render at an offset based on the camera
    dst_r.x = vx + (int) x;
    dst_r.y = vy + (int) y;
    dst_r.w = w;
    dst_r.h = h;

    //TODO: only render things that will be on screen
    SDL_RenderCopyEx(renderer, texture, &src_r, &dst_r, 0.0, NULL, direction > 4 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

double GameObject::cx() {
    return x + base_x_offset;
}

double GameObject::cy() {
    return y + base_y_offset;
}

bool GameObject::collide(double mx, double my, GameObject* other) {
    return ((cx() + mx < other->cx() + other->pw) && (cx() + mx + pw > other->cx())) 
        && ((cy() + my < other->cy() + other->ph) && (cy() + my + ph > other->cy()));
}

void GameObject::update(double dt) {
    double mx = dx * dt;
    double my = dy * dt;
    // only check collisions for moviing objects
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

    // set the direction of the player - 0 through 8 otc
    if (close_to_zero(dx)) {
        if (dy < -EPS)
            direction = 0;
        else if (dy > EPS)
            direction = 4;
    }
    else if (dx > EPS) {
        if (dy < -EPS)
            direction = 1;
        else if (close_to_zero(dy))
            direction = 2;
        else if (dy > EPS)
            direction = 3;
    }
    else if (dx < -EPS) {
        if (dy < -EPS)
            direction = 7;
        else if (close_to_zero(dy))
            direction = 6;
        else if (dy > EPS)
            direction = 5;
    }

}
