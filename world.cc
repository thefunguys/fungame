#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "world.h"
#include "gameobject.h"
#include "player.h"
#include "sprite.h"
#include "split.h"

bool gobjComp(GameObject* go1, GameObject* go2) {
    return go1->pos.y < go2->pos.y;
}

void World::render(sf::RenderWindow& window, int vx, int vy) {
    //objects look like they are in front of others
    //may have to change if we add too many objects
    std::sort(gobjs.begin(), gobjs.end(), gobjComp);
    for (GameObject* gobj : gobjs) {
        gobj->render(window, vx, vy);
    }
    sf::Texture* smap = shadowmap(cur_player->pos.x + 16, cur_player->pos.y + 16);
    sf::Sprite sp_smap(*smap);
    delete smap;
}

sf::Texture* World::shadowmap(float lsx, float lsy) {
    sf::Texture* map = new sf::Texture;
    map->create(640, 480);
    sf::Uint8* pxs = new sf::Uint8[640 * 480 * 4];
    for (int i = 0; i < 640; i++) {
        for (int j = 0; j < 480; j++) {
            float dist2 = (lsx - i) * (lsx - i) + (lsy - j) * (lsy - j);
            pxs[i] = 0xff / ((sf::Uint8) dist2 + 1);
            pxs[i + 1] = 0xff / ((sf::Uint8) dist2 + 1);
            pxs[i + 2] = 0xff / ((sf::Uint8) dist2 + 1);
            pxs[i + 3] = 0xff;
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

World::World(std::string lvlname) {
    /* lvls are denoted by files
     * each line represents a GameObject
     * class specifier, texture name, w, h, ss_w, ss_h, x, y
     * until the last line, which is "end"
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
        }
        std::getline(lvl, cur_line);
    }
}
