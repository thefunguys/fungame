#include <cmath>
#include <stdio.h>
#include "game.h"
#include "gameobject.h"
#include "fns.h"
#include "shadermanager.h"

GameObject::GameObject(std::string fname,
                       int nx, int ny, int nw, int nh, int nl) : boundary(nw, nl, 10) {
    texture.loadFromFile(fname);
    sprite.setTexture(texture);
    shader = nullptr;

    pVector tmp( (double) nx, (double) ny);
    pos = tmp;
    sprite.setPosition(pos.x, pos.y);
    focused = false;

    w = nw;
    h = nh;
    l = nl;

    direction = 2;

    mass = 1.0;
}

void GameObject::render(sf::RenderWindow& window, bool shadered) {
    if (!shadered) {
        window.draw(sprite);
        return;
    }
    sf::Shader* ssh = shader;
    if (ssh == nullptr)
        ssh = ShaderManager::instance()->goShader;
    auto highlight = focused ? sf::Vector3f(1.0, 0.0, 0.0) : sf::Vector3f(1.0, 1.0, 1.0);
    ssh->setParameter("highlight", highlight);
    window.draw(sprite, ssh);
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
    if (close_to_zero(vel.x) && close_to_zero(vel.y)) {
        return;
    }
    // -180 to 180
    //    0
    //  7   1
    // 6     2
    //  5   3
    //    4
    double angle = std::atan2(vel.y, vel.x) * 180.0 / M_PI;
    if (angle < 135.0 && angle >= 45.0) {
        direction = 4;
    } else if (angle < 45.0 && angle >= -45.0) {
        direction = 2;
    } else if (angle < -45.0 && angle >= -135.0) {
        direction = 0;
    } else if (angle < -135.0 || angle > 135.0) {
        direction = 6;
    }
}

sf::Vector2i GameObject::windowPos(sf::Window& window) {
    return wpos(window, pos.x, pos.y);
}

sf::Vector2f gpos(sf::Window& window, int x, int y) {
    auto ws = window.getSize();
    auto abc = sf::Vector2i(x * GAME_WIDTH / ws.x, y * GAME_HEIGHT / ws.y);
    auto di = sf::Vector2i(GAME_WIDTH / 2 - 16, GAME_HEIGHT / 2 - 16) - abc;
    auto p = Game::p;
    return sf::Vector2f(p->pos.x - di.x, p->pos.y - di.y);
}

sf::Vector2i wpos(sf::Window& window, float x, float y) {
    auto ws = window.getSize();
    // the game shows a GAME_WIDTHxGAME_HEIGHT viewport centered around the player
    auto p = Game::p;
    auto diff = sf::Vector2i(p->pos.x - x, p->pos.y - y);
    auto abc = sf::Vector2i(GAME_WIDTH / 2 - 16, GAME_HEIGHT / 2 + 16) - diff;
    return sf::Vector2i(abc.x * ws.x / GAME_WIDTH, abc.y * ws.y / GAME_HEIGHT);
}

