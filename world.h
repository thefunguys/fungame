#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include "gameobject.h"

class World {
    public:
    std::vector<GameObject*> gobjs;
    void render(SDL_Renderer*, int, int);
    void update(double dt);
    void add_gameobject(GameObject*);
};

#endif
