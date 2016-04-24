#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"

using namespace std;

Game::Game(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to init SDL: " << SDL_GetError() << endl;
        return;
    }

    window = SDL_CreateWindow("super cool game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            w, h, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return;
    }

    surface = SDL_GetWindowSurface(window);
}

SDL_Window* Game::getWindow() {
    if (!window) {
        cerr << "getWindow() called on null window" << endl;
    }
    return window;
}

SDL_Surface* Game::getSurface() {
    if (!surface) {
        cerr << "getSurface() called on null surface" << endl;
    }
    return surface;
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
