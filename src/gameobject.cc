#include <cmath>
#include <stdio.h>
#include "game.h"
#include "gameobject.h"
#include "fns.h"
#include "shadermanager.h"

GameObject::GameObject(std::string fname,
                       int nx, int ny, int nw, int nh, int ncw, int nch) : boundary(nw, ncw, nch) {
    shadowcasts = true;
    texture.loadFromFile(fname);
    sprite.setTexture(texture);
    shader = nullptr;

    pVector tmp( (double) nx, (double) ny);
    pos = tmp;
    sprite.setPosition(pos.x, pos.y);
    focused = false;

    w = nw;
    h = nh;
    pw = ncw;
    ph = nch;

    direction = 2;

    mass = 1.0;
}

void GameObject::render(sf::RenderTarget& window, bool shadered) {
    if (!shadered) {
        window.draw(sprite);
        return;
    }
    sf::Shader* ssh = shader;
    if (ssh == nullptr) {
        ssh = ShaderManager::instance()->goShader;
    }
    auto highlight = focused ? sf::Vector3f(1.0, 0.0, 0.0) : sf::Vector3f(1.0, 1.0, 1.0);
    ssh->setParameter("highlight", highlight);
    window.draw(sprite, ssh);
}

bool checkCollide(GameObject* go, GameObject* ogo, pVector mpos, pVector vel) {
    pVector diff = ogo->pos - go->pos - mpos;
    Boundary moving;
    moving.diameter = go->boundary.diameter;
    for (pVector &p : go->boundary.boundary ) {
        if(p.dot(mpos) > 0 ) {
            moving.boundary.push_back(p + mpos);
        } else {
            moving.boundary.push_back(p);
        }
    }
    return moving.collision(ogo->boundary, diff, vel);
}


void GameObject::update(double dt) {
    pVector mpos(vel.x * dt, vel.y * dt);

    // obly check collisions for moviing objects
    if (fabs(mpos.x) > 0.005 || fabs(mpos.y) > 0.005) {
        for (GameObject* ogo : Game::current_world->gobjs) {
            if (ogo != this) {
                if (checkCollide(this, ogo, {mpos.x, 0}, {vel.x, 0})) {
                    mpos.x = 0;
                }
                if (checkCollide(this, ogo, {0, mpos.y}, {0, vel.y})) {
                    mpos.y = 0;
                }
            }
        }
    }
    pos = pos + mpos;
    sprite.move(mpos.x, mpos.y);
    if (close_to_zero(vel.x) && close_to_zero(vel.y)) {
        return;
    }
    double angle = std::atan2(vel.y, vel.x) * 180.0 / M_PI - 27.5;
    direction = (12 - ((int) (10 - angle / 45.)) % 8 ) % 8;
}

sf::Vector2i GameObject::windowPos(sf::RenderTarget& window) {
    return wpos(window, pos.x, pos.y);
}

sf::Vector2f gpos(sf::RenderTarget& window, int x, int y) {
    auto ws = window.getSize();
    auto abc = sf::Vector2i(x * GAME_WIDTH / ws.x, y * GAME_HEIGHT / ws.y);
    auto di = sf::Vector2i(GAME_WIDTH / 2 - 16, GAME_HEIGHT / 2 - 16) - abc;
    auto p = Game::p;
    return sf::Vector2f(p->pos.x - di.x, p->pos.y - di.y);
}

sf::Vector2i wpos(sf::RenderTarget& window, float x, float y) {
    auto ws = sf::Vector2i(GAME_WIDTH, GAME_HEIGHT);
    // the game shows a GAME_WIDTHxGAME_HEIGHT viewport centered around the player
    auto p = Game::p;
    auto diff = sf::Vector2i(p->pos.x - x, p->pos.y - y);
    auto abc = sf::Vector2i(GAME_WIDTH / 2 - 16, GAME_HEIGHT / 2 - 16) - diff;
    return sf::Vector2i(abc.x * ws.x / GAME_WIDTH, abc.y * ws.y / GAME_HEIGHT);
}

sf::Vector2f wpos(sf::RenderTarget& window, sf::Vector2f v) {
    auto vi = wpos(window, v.x, v.y);
    return sf::Vector2f(vi.x, vi.y);
}
