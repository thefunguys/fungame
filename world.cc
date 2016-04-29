#include "world.h"
#include "gameobject.h"

void World::render(SDL_Renderer* renderer) {
    for (GameObject gobj : gobjs) {
        gobj.render(renderer);
    }
}

void World::update(double dt) {

}
