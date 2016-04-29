#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include "gameobject.h"

class World {
    public:
    std::vector<GameObject> gobjs;
    void render(SDL_Renderer*);
    void update(double dt);
};

#endif
