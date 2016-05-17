#ifndef GAME_H
#define GAME_H

#include <map>
#include "world.h"

class Game {
    const int FPS = 45;
    void init_gl();
    World* world;

  public:
    static World* current_world;
    Game(int, int);
    ~Game();
    sf::RenderWindow window;
    void loop();
};

#endif
