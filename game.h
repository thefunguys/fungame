#include <map>

class Game {
    const int FPS = 60;
    SDL_Window* window;
    SDL_Surface* surface;
    std::map<SDL_Keycode, int> keymap;

public:
    Game(int, int);
    ~Game();
    SDL_Window* getWindow();
    SDL_Surface* getSurface();
    void loop();
};
