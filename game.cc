#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"
#include "keymap.h"
#include "player.h"

using namespace std;

Game::Game(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to init SDL: " << SDL_GetError() << endl;
        return;
    }

    window = SDL_CreateWindow("super cool game", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!renderer) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
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

SDL_Renderer* Game::getRenderer() {
    if (!renderer) {
        cerr << "getRenderer() called on null renderer" << endl;
    }
    return renderer;
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::loop() {
    bool running = true;
    SDL_Event e;
    // in this loop we handle input, process events, draw all things, update 
    // the window, and wait until the next frame
    Player* blackguy = new Player("blackman.bmp", renderer, 100, 400, 32, 32);
    world.add_gameobject(blackguy);
    int lastupdate = SDL_GetTicks();
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                cout << "Received exit signal" << endl;
            }
            else if (e.type == SDL_KEYDOWN) {
                Keymap::keymap[e.key.keysym.sym] = 1;
            }
            else if (e.type == SDL_KEYUP) {
                Keymap::keymap[e.key.keysym.sym] = 0;
            }
        }

        SDL_RenderClear(renderer);
        world.update((SDL_GetTicks() - lastupdate) * 0.001);
        world.render(renderer);
        SDL_RenderPresent(renderer);
        lastupdate = SDL_GetTicks();
        SDL_Delay(1000/FPS);
    }
}
