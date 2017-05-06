#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "world.h"
#include "gameobject.h"
#include "player.h"
#include "sprite.h"
#include "shadermanager.h"
#include "rat.h"
#include "fns.h"
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

glm::vec2 gls;
sf::RenderTexture rt;

glm::vec2 sfToGlm(sf::Vector2f &v) {
    return glm::vec2(v.x, v.y);
}
bool gobjComp(GameObject* go1, GameObject* go2) {
    if (close_to_zero(go1->pos.y + go1->h - go2->pos.y + go2->h)) {
        return go1->pos.x < go2->pos.x;
    }
    return go1->pos.y + go1->h < go2->pos.y + go2->h;
}

bool vertComp(sf::Vector2f &v1, sf::Vector2f &v2) {
    return glm::length(sfToGlm(v1) - gls) > glm::length(sfToGlm(v2) - gls);
}

bool gobjVComp(GameObject* go1, GameObject* go2) {
    auto v1 = sf::Vector2f(go1->pos.x, go1->pos.y);
    auto v2 = sf::Vector2f(go2->pos.x, go2->pos.y);
    return vertComp(v1, v2);
}

float dotProd(sf::Vector2f &v1, sf::Vector2f &v2) {
    return v1.x * v2.x + v1.y * v2.y;
}


sf::Vector2f glmToSf(glm::vec2 &v) {
    return sf::Vector2f(v.x, v.y);
}

//TODO: make this based off absolute positions
//      so it can be just as big as the view
const sf::Texture& World::lightmap(sf::Vector2f ls, int lsHeight,
                                   GameObject* exclude, sf::RenderTarget& window) {
    rt.clear(sf::Color::White);
    auto lswpos = wpos(window, ls);
    auto glmls = sfToGlm(lswpos);
    gls = glmls;

    // drawing starts at the furthest objects
    std::sort(gobjs.begin(), gobjs.end(), gobjVComp);
    std::reverse(gobjs.begin(), gobjs.end());

    for (auto go : gobjs) {
        if (go == exclude || !go->shadowcasts) {
            continue;
        }
        auto windowVec = glm::vec2(1000, 1000);
        if (go->height < lsHeight) {
            auto objdist = glm::length(sfToGlm(ls) - glm::vec2(go->pos.x, go->pos.y));
            auto shlen = objdist * go->height / (lsHeight - go->height);
            windowVec = glm::vec2(shlen, shlen);
        }
        std::vector<sf::Vector2f> vertices;
        for (auto &bVec : go->boundary.boundary) {
            vertices.push_back(wpos(window,
                            sf::Vector2f(go->pos.x + bVec.x,
                                         go->pos.y + go->h - bVec.y)));
        }

        /**
         * for every pair of adjacent vertices in the gameobject, we find
         * the 4-sided polygon that it occludes from the light source, and
         * draw that to the shadowmap
         */
        for (size_t i = 0; i < vertices.size(); ++i) {
            auto v1 = sfToGlm(vertices[i]);
            // count the wrap around
            auto v2 = sfToGlm(vertices[i == vertices.size() - 1 ? 0 : i + 1]);

            // project the vertices onto the window edge
            auto proj1 = v1 + glm::normalize(v1 - glmls) * windowVec;

            auto proj2 = v2 + glm::normalize(v2 - glmls) * windowVec;

            auto lightshape = sf::ConvexShape(4);
            lightshape.setFillColor(sf::Color(12, 12, 19, 200));
            lightshape.setPoint(0, glmToSf(v1));
            lightshape.setPoint(1, glmToSf(proj1));
            lightshape.setPoint(2, glmToSf(proj2));
            lightshape.setPoint(3, glmToSf(v2));

            rt.draw(lightshape);

        }
        // objects shouldn't shade themselves or shorter objects
        for (auto gon : gobjs) {
            if (gon->height >= go->height) {
                auto gosp = gon->sprite;
                gosp.setPosition(wpos(window, gosp.getPosition()));
                rt.draw(gosp, ShaderManager::instance()->whiteShader);
            }
        }
    }
    rt.display();
    // we must reverse again or else objects will not be drawn from left to 
    // right -- FIX THIS
    std::reverse(gobjs.begin(), gobjs.end());
    return rt.getTexture();
}

void World::render(sf::RenderWindow& window) {
    //objects look like they are in front of others
    //may have to change if we add too many objects
    std::sort(gobjs.begin(), gobjs.end(), gobjComp);

    // MAY CAUSE SEIZURES
    float flicker = rand() % 100 * 0.002 + 0.8;
    float dirx = 0.0, diry = 0.0;

    if(cur_player->direction == 0 || cur_player->direction == 1 || cur_player->direction == 7) {
        diry = 1;
    } else if(cur_player->direction >= 3 && cur_player->direction <= 5) {
        diry = -1;
    } else if(cur_player->direction == 2 || cur_player->direction == 6) {
        diry = 0;
    }
    if(cur_player->direction >= 1 && cur_player->direction <= 3) {
        dirx = 1;
    } else if(cur_player->direction >= 5 && cur_player->direction <= 7) {
        dirx = -1;
    } else if(cur_player->direction == 0 || cur_player->direction == 4) {
        dirx = 0;
    }
    
    auto pvel = glm::vec2(cur_player->lastDir.x, cur_player->lastDir.y);
    auto pvel_norm = glm::normalize(pvel);
    if (!(close_to_zero(pvel.x) && close_to_zero(pvel.y))) {
        dirx = pvel_norm.x;
        diry = -pvel_norm.y;
    }

    auto ws = window.getSize();
    for (auto shader : ShaderManager::instance()->shaders) {
        shader->setParameter("texture", sf::Shader::CurrentTexture);
        shader->setParameter("flicker", flicker);
        shader->setParameter("windowsize", ws.x, ws.y);
        shader->setParameter("direction", dirx, diry);
    }
    GameObject* focused = nullptr;
    for (auto gobj : gobjs) {
        if (gobj == cur_player) {
            continue;
        }
        gobj->focused = false;
        auto mpos = sf::Mouse::getPosition(window);
        auto fr = gobj->sprite.getGlobalBounds();
        auto gmpos = gpos(window, mpos.x, mpos.y);
        if (fr.contains(gmpos)) {
            focused = gobj;
        }
    }
    if (focused != nullptr) {
        focused->focused = true;
    }

    bg.render(window);
    for (GameObject* gobj : gobjs) {
        gobj->render(window);
    }
    /*
    std::vector<sf::Vector2f> lightsources;
    lightsources.push_back(sf::Vector2f(300, 300));
    for (auto ls : lightsources) {
        auto lm = lightmap(ls, 500, nullptr, window);
        sf::Sprite sp(lm);
        auto rs = sf::RenderStates(sf::BlendMultiply);
        auto view = sf::View(sf::FloatRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
        window.setView(view);
        window.draw(sp, rs);
    }
    */
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

    bg("assets/background.png", 0, 0, 1000, 1000, 1000, 1000) {
    /* lvls are denoted by files
     * each line represents a GameObject
     * class specifier, texture name, w, h, ss_w, ss_h, x, y
     * until the last line, which is "end"
     *
     * TODO: use json or yaml or something sane
     * see https://github.com/nlohmann/json
     * */

    rt.create(GAME_WIDTH, GAME_HEIGHT);
    std::ifstream lvl(lvlname);
    std::string cur_line = "";
    std::getline(lvl, cur_line);
    while (cur_line != "end") {
        std::vector<std::string> toks = split(cur_line, ' ');
        if( toks[0][0] == '/' && toks[0][1] == '/' ) {
            std::getline(lvl, cur_line);
            continue;
        }
        std::string asset = "assets/" + toks[1] + ".png";
        int w;
        int h;
        int ss_h;
        int ss_w;
        int x;
        int y;
        int boun_w, boun_h;
        std::stringstream(toks[2]) >> w;
        std::stringstream(toks[3]) >> h;
        std::stringstream(toks[4]) >> ss_w;
        std::stringstream(toks[5]) >> ss_h;
        std::stringstream(toks[6]) >> x;
        std::stringstream(toks[7]) >> y;
        std::stringstream(toks[8]) >> boun_w;
        std::stringstream(toks[9]) >> boun_h;
        if (toks[0] == "player") {
            dbpf("adding player\n");
            Player* p = new Player(asset, x, y, w, h, 10, 10);
            p->name = "player";
            p->ss_w = ss_w;
            p->ss_h = ss_h;
            add_gameobject(p);
            cur_player = p;
        } else if (toks[0] == "sprite") {
            Sprite* s = new Sprite(asset, x, y, w, h, 3 * w / 4, h / 5);
            s->name = toks[1];
            s->ss_w = ss_w;
            s->ss_h = ss_h;
            add_gameobject(s);
        } else if (toks[0] == "rat") {
            Rat* r = new Rat(asset, x, y, w, h, 5, 5);
            r->name = "rat";
            r->ss_w = ss_w;
            r->ss_h = ss_h;
            add_gameobject(r);
        }
        std::getline(lvl, cur_line);
    }
}
