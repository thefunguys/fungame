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

void World::render(SDL_Renderer* renderer, int vx, int vy) {
    //objects look like they are in front of others
    //may have to change if we add too many objects
    std::sort(gobjs.begin(), gobjs.end(), gobjComp);
    for (GameObject* gobj : gobjs) {
        gobj->render(renderer, vx, vy);
    }
}

void World::add_gameobject(GameObject* gameobject) {
    gobjs.push_back(gameobject);
}

void World::update(double dt) {
    for (GameObject* g : gobjs) {
        g->update(dt);
    }
}

World::World(std::string lvlname, SDL_Renderer* r) {
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
            Player* p = new Player(asset, r, x, y, w, h, 1);
            p->ss_w = ss_w;
            p->ss_h = ss_h;
            add_gameobject(p);
            cur_player = p;
        }
        else if (toks[0] == "sprite") {
            Sprite* s = new Sprite(asset, r, x, y, w, h, 1);
            s->ss_w = ss_w;
            s->ss_h = ss_h;
            add_gameobject(s);
        }
        std::getline(lvl, cur_line);
    }
}
