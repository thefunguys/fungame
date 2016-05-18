#include <iostream>
#include <cmath>
#include "game.h"
#include "gameobject.h"
#include "fns.h"

GameObject::GameObject(std::string fname,
                       int nx, int ny, int nw, int nh, int nl) : bountry(nw, nl, 10) {
    texture.loadFromFile(fname);
    sprite.setTexture(texture);
    shader.loadFromFile("shader.frag", sf::Shader::Fragment);
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    sf::Vector2f wh((float) nw, (float) nh);
    shader.setParameter("wh", wh);

    pVector tmp( (double) nx, (double) ny);
    pos = tmp;
    sprite.setPosition(pos.x, pos.y);

    w = nw;
    h = nh;
    l = nl;

    direction = 2;

    mass = 1.0;
}

void GameObject::render(sf::RenderWindow& window, int vx, int vy, bool shadered) {
    if (!shadered) {
        window.draw(sprite);
        return;
    }
    float flicker = random() % 100 * 0.01 / 10 + 0.9;
    shader.setParameter("flicker", flicker);
    shader.setParameter("dxy", sf::Vector2f(Game::p->pos.x + 16 - pos.x, Game::p->pos.y + 16 - pos.y));
    window.draw(sprite, &shader);
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
    sprite.move(mpos.x, mpos.y);

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
