#ifndef GAME_H
#define GAME_H

#include <map>
#include "world.h"
#include "player.h"

#define GAME_WIDTH 320
#define GAME_HEIGHT 240

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
