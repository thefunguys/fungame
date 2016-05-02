#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "game.h"
#include "LTexture.h"
#include "gameobject.h"
#include "fns.h"

GameObject::GameObject(std::string fname, SDL_Renderer* renderer,
                       int nx, int ny, int nw, int nh, int nl) : bountry(nw, nl) {
    if (!texture.loadTextureFromFile(fname)) {
        std::cerr << "failed to load texture " << fname << std::endl;
    }

    pVector tmp( (double) nx, (double) ny);
    pos = tmp;

    w = nw;
    h = nh;
    l = nl;


    direction = 2;

    mass = 1.0;
}

void GameObject::render(int vx, int vy) {
    /*SDL_Rect src_r;
    SDL_Rect dst_r;

    src_r.x = 0;
    src_r.y = 0;
    src_r.w = w;
    src_r.h = h;*/


    //TODO: only render things that will be on screen
    //SDL_RenderCopyEx(renderer, texture, &src_r, &dst_r, 0.0, NULL, direction > 4 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    texture.render((float) pos.x + (float) vx, (float) pos.y + (float) vy);
}




void GameObject::update(double dt) {
    pVector mpos(vel.x * dt, vel.y * dt);

    // obly check collisions for moviing objects
    if (fabs(mpos.x) > 0.005 || fabs(mpos.y) > 0.005) {
        for (GameObject* ogo : Game::current_world->gobjs) {
            if (ogo != this) {
                pVector diff = ogo->pos - this->pos - mpos;
                Bountry moving;
                moving.diameter = this->bountry.diameter;
                for (pVector &p : this->bountry.bountry ) {
                    if(p.dot(mpos) > 0 ) {
                        moving.bountry.push_back(p + mpos);
                    } else {
                        moving.bountry.push_back(p);
                    }
                }
                if (moving.collision(ogo->bountry, diff, vel)) {
                    mpos = {0, 0};
                }
            }
        }
    }
    pos = pos + mpos;

    // set the direction of the player - 0 through 8 otc
    if (close_to_zero(vel.x)) {
        if (vel.y < -EPS) {
            direction = 0;
        } else if (vel.y > EPS) {
            direction = 4;
        }
    } else if (vel.x > EPS) {
        if (vel.y < -EPS) {
            direction = 1;
        } else if (close_to_zero(vel.y)) {
            direction = 2;
        } else if (vel.y > EPS) {
            direction = 3;
        }
    } else if (vel.x < -EPS) {
        if (vel.y < -EPS) {
            direction = 7;
        } else if (close_to_zero(vel.y)) {
            direction = 6;
        } else if (vel.y > EPS) {
            direction = 5;
        }
    }

}
