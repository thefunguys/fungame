#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include "gameobject.h"
#include "player.h"

class World {
  public:
    std::vector<GameObject*> gobjs;
    void render(int, int);
    void update(double dt);
    void add_gameobject(GameObject*);
    Player* cur_player;
    World(std::string, SDL_Renderer*);

    std::vector<GameObject*> walls;
};

#endif
