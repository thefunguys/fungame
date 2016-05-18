#include <iostream>
#include "gameobject.h"
#include "sprite.h"
#include "fns.h"

const double FRAME_SWITCH = 0.3;

Sprite::Sprite(std::string fname, int x, int y, int w, int h, int l) : GameObject::GameObject(fname, x, y, w, h, l) {
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
        if (++curframe_x >= ss_w) {
            curframe_x = 0;
        }
        frame_t = 0;
    }
    if (close_to_zero(vel.x) && close_to_zero(vel.y)) {
        curframe_x = 0;
    }
    GameObject::update(dt);
    switch (direction)
    {
        case 0:
            curframe_y = 1;
            break;
        case 1:
        case 2:
        case 3:
            curframe_y = 0;
            break;
        case 4:
            curframe_y = 2;
            break;
        default:
            curframe_y = 3;
            break;
    }
}

void Sprite::render(sf::RenderWindow& window, int vx, int vy) {
    /*SDL_Rect src_r;
    SDL_Rect dst_r;*/
//    LFRect src_r = {0.0, 0.0, (GLfloat) w, (GLfloat) h};

    //src_r.x = (GLfloat) (curframe_x * w);
    //src_r.y = (GLfloat) (curframe_y * h) + 1.0;
    //src_r.w = (GLfloat) w;
    //src_r.h = (GLfloat) h - 1.0;
/*
    dst_r.x  = vx + (int) pos.x;
    dst_r.y = vy + (int) pos.y;
    dst_r.w = w;
    dst_r.h = h;

    SDL_RenderCopyEx(renderer, texture, &src_r, &dst_r, 0.0, NULL,
                     direction > 4 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
                     */
  //  texture.render((GLfloat) (pos.x + vx), (GLfloat) (pos.y + vy), &src_r);
  //  GameObject::render(window, vx, vy);

    sprite.setTextureRect(sf::IntRect(curframe_x * w, curframe_y * h, w, h));
    GameObject::render(window, vx, vy);
}
