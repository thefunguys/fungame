#include "world.h"
#include "gameobject.h"

void World::render(SDL_Renderer* renderer) {
    for (GameObject* gobj : gobjs) {
        gobj->render(renderer);
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
