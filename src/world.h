#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "gameobject.h"
#include "player.h"
#include "glm.h"
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"

class World {
  public:
    std::vector<GameObject*> gobjs;
    std::vector<GameObject*> bg_gobjs;
    void render(sf::RenderWindow&);
    Sprite bg;
    sf::Texture* shadowmap(float, float);
    const sf::Texture& lightmap(sf::Vector2f ls, int lsHeight, GameObject* exclude, sf::RenderTarget& window);
    void update(double dt);
    void add_gameobject(GameObject*);
    Player* cur_player;
    World(std::string);
    std::vector<GameObject*> walls;
    tmx::Map map;
    std::vector<MapLayer*> layers;
    bool can_move_to(GameObject* go, sf::Vector2f pos);
};



#endif
