class Game {
    const int FPS = 60;
    SDL_Window* window;
    SDL_Surface* surface;

public:
    Game(int, int);
    ~Game();
    SDL_Window* getWindow();
    SDL_Surface* getSurface();
    void loop();
};
