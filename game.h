#include <map>

class Game {
    const int FPS = 60;
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    SDL_GLContext glContext;
    std::map<SDL_Keycode, int> keymap;

public:
    Game(int, int);
    ~Game();
    SDL_Window* getWindow();
    SDL_Surface* getSurface();
    SDL_Renderer* getRenderer();
    void loop();
};
