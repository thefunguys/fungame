#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "gameobject.h"
#include "player.h"

class World {
  public:
    std::vector<GameObject*> gobjs;
    void render(sf::RenderWindow&);
    Sprite bg;
    sf::Texture* shadowmap(float, float);
    void update(double dt);
    void add_gameobject(GameObject*);
    Player* cur_player;
    World(std::string);

    std::vector<GameObject*> walls;
};

#endif
