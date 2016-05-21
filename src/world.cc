#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include "world.h"
#include "gameobject.h"
#include "player.h"
#include "sprite.h"
#include "shadermanager.h"
#include "rat.h"
#include "fns.h"

bool gobjComp(GameObject* go1, GameObject* go2) {
    return go1->pos.y + go1->h < go2->pos.y + go2->h;
}

void World::render(sf::RenderWindow& window) {
    //objects look like they are in front of others
    //may have to change if we add too many objects
    std::sort(gobjs.begin(), gobjs.end(), gobjComp);

    // MAY CAUSE SEIZURES
    float flicker = random() % 100 * 0.002 + 0.8;

    for (auto shader : ShaderManager::instance()->shaders) {
        shader->setParameter("texture", sf::Shader::CurrentTexture);
        shader->setParameter("flicker", flicker);
        shader->setParameter("windowsize", window.getSize().x, window.getSize().y);
    }

    bg.render(window);
    for (GameObject* gobj : gobjs) {
        gobj->render(window);
    }
}

// TODO: make multithreaded somehow -- it's a real cpu hog
// deprecated, but an example of texture editing
sf::Texture* World::shadowmap(float lsx, float lsy) {
    sf::Texture* map = new sf::Texture;
    map->create(640, 480);
    sf::Uint8* pxs = new sf::Uint8[640 * 480 * 4];
    for (int i = 0; i <= 320; i++) {
        for (int j = 0; j <= 240; j++) {
            float dist2 = (lsx - i) * (lsx - i) + (lsy - j) * (lsy - j);
            int offsets [4] = {
                4 * (i + 640 * j),
                4 * (640 - i + 640 * (480 - j)),
                4 * (i + 640 * (480 - j - 1)),
                4 * (640 - i + 640 * j)
            };
            int dampen = (int) 255.0 * (1000.0 / (dist2 + 1000.0));
            for (int k = 0; k < 4; ++k) {
                int offset = offsets[k];
                pxs[offset]     = (sf::Uint8) dampen;
                pxs[offset + 1] = (sf::Uint8) dampen;
                pxs[offset + 2] = (sf::Uint8) dampen;
                pxs[offset + 3] = 0xff;
            }
        }
    }

    map->update(pxs);
    delete pxs;

    return map;
}

void World::add_gameobject(GameObject* gameobject) {
    gobjs.push_back(gameobject);
}

void World::update(double dt) {
    for (GameObject* g : gobjs) {
        g->update(dt);
    }
}

World::World(std::string lvlname) :
    // maybe make the background texture from something cool like voronai
    bg("assets/background.png", 0, 0, 1000, 1000, 0) {
    /* lvls are denoted by files
     * each line represents a GameObject
     * class specifier, texture name, w, h, ss_w, ss_h, x, y
     * until the last line, which is "end"
     *
     * TODO: use json or yaml or something sane
     * see https://github.com/nlohmann/json
     * */
    std::ifstream lvl(lvlname);
    std::string cur_line = "";

    std::getline(lvl, cur_line);
    while (cur_line != "end") {
        std::vector<std::string> toks = split(cur_line, ' ');
        std::string asset = "assets/" + toks[1];
        int w;
        int h;
        int ss_h;
        int ss_w;
        int x;
        int y;
        std::stringstream(toks[2]) >> w;
        std::stringstream(toks[3]) >> h;
        std::stringstream(toks[4]) >> ss_w;
        std::stringstream(toks[5]) >> ss_h;
        std::stringstream(toks[6]) >> x;
        std::stringstream(toks[7]) >> y;
        if (toks[0] == "player") {
            std::cout << "adding player" << std::endl;
            Player* p = new Player(asset, x, y, w, h, 1);
            p->ss_w = ss_w;
            p->ss_h = ss_h;
            add_gameobject(p);
            cur_player = p;
        } else if (toks[0] == "sprite") {
            Sprite* s = new Sprite(asset, x, y, w, h, 10);
            s->ss_w = ss_w;
            s->ss_h = ss_h;
            add_gameobject(s);
        } else if (toks[0] == "rat") {
            Rat* r = new Rat(asset, x, y, w, h, 5);
            r->ss_w = ss_w;
            r->ss_h = ss_h;
            add_gameobject(r);
        }
        std::getline(lvl, cur_line);
    }
}
