#ifndef GAME_H
#define GAME_H

#include <map>
#include "world.h"

class Game {
    const int FPS = 60;
    void init_gl();
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    World* world;

  public:
    static World* current_world;
    Game(int, int);
    ~Game();
    SDL_Window* getWindow();
    SDL_Surface* getSurface();
    SDL_Renderer* getRenderer();
    void loop();
};

#endif
