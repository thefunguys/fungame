#include <algorithm>
#include "world.h"
#include "gameobject.h"

bool gobjComp(GameObject* go1, GameObject* go2) {
    return go1->y < go2->y;
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
