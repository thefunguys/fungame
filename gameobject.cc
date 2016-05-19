#include <iostream>
#include <cmath>
#include "game.h"
#include "gameobject.h"
#include "fns.h"
#include "shadermanager.h"

GameObject::GameObject(std::string fname,
                       int nx, int ny, int nw, int nh, int nl) : boundary(nw, nl, 10) {
    texture.loadFromFile(fname);
    sprite.setTexture(texture);

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
    sf::Shader* shader = ShaderManager::goShader;
    window.draw(sprite, shader);
}




void GameObject::update(double dt) {
    pVector mpos(vel.x * dt, vel.y * dt);

    // obly check collisions for moviing objects
    if (fabs(mpos.x) > 0.005 || fabs(mpos.y) > 0.005) {
        for (GameObject* ogo : Game::current_world->gobjs) {
            if (ogo != this) {
                pVector diff = ogo->pos - this->pos - mpos;
                Boundary moving;
                moving.diameter = this->boundary.diameter;
                for (pVector &p : this->boundary.boundary ) {
                    if(p.dot(mpos) > 0 ) {
                        moving.boundary.push_back(p + mpos);
                    } else {
                        moving.boundary.push_back(p);
                    }
                }
                if (moving.collision(ogo->boundary, diff, vel)) {
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
