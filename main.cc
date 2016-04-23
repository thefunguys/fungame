#include <SDL2/SDL.h>
#include <iostream>
#include "game.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;

int main(int argc, char ** argv) {
    bool running = true;
    int exit_code = 0;
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);


    int ticks = 0;
    SDL_Event e;
    // in this loop we handle input, process events, draw all things, update 
    // the window, and wait until the next frame
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                cout << "Received exit signal" << endl;
            }
        }
        SDL_FillRect(game.getSurface(), NULL, SDL_MapRGB(game.getSurface()->format, 0xff, 0xff, 0xff));

        SDL_UpdateWindowSurface(game.getWindow());
        SDL_Delay(1000/FPS);
    }

    SDL_Quit();
    return exit_code;
}

