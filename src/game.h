#ifndef GAME_H
#define GAME_H

#include <map>
#include "world.h"
#include "player.h"

const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

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
    static sf::RenderWindow* cur_window;
    void loop();
};

#endif
