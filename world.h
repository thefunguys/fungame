#include <vector>
#include <SDL2/SDL.h>
#include "game.h"
#include "gameobject.h"

class World {
    Game* game;
    public:
    std::vector<GameObject> gobjs;
    void render();
};
