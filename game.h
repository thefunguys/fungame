#ifndef GAME_H
#define GAME_H

#include <map>
#include "world.h"
#include "player.h"

class Game {
    const int FPS = 60;
    void init_gl();
    World* world;

  public:
    static World* current_world;
    static Player* p;
    Game(int, int);
    ~Game();
    sf::RenderWindow window;
    void loop();
};

#endif
