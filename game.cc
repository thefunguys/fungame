#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "keymap.h"
#include "player.h"
#include "sprite.h"

using namespace std;

World* Game::current_world;

Game::Game(int w, int h) {
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to init SDL: " << SDL_GetError() << endl;
        return;
    }

    window = SDL_CreateWindow("super cool game", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!renderer) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        return;
    }

    IMG_Init(IMG_INIT_PNG);

    world = new World("levels/test.lvl", renderer);
    surface = SDL_GetWindowSurface(window);
    current_world = world;
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

    //for (int i = 0; i < 10; ++i) {
    //    world.add_gameobject(new Sprite("assets/box.png", renderer, rand() % 640, rand() % 480, 32, 32));
    //}
    //Player* blackguy = new Player("assets/blackman.png", renderer, 100, 400, 32, 32);
    SDL_Rect vp;
    //world.add_gameobject(blackguy);
    int lastupdate = SDL_GetTicks();
    Player* blackguy = World::cur_player;
    cout << blackguy->x << endl;
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

        SDL_SetRenderDrawColor(renderer, 43, 26, 13, 255);
        SDL_RenderClear(renderer);
        world->update((SDL_GetTicks() - lastupdate) * 0.001);
        lastupdate = SDL_GetTicks();
        vp.x = 320 - blackguy->x;
        vp.y = 240 - blackguy->y;
        vp.w = 640;
        vp.h = 480;
        world->render(renderer, vp.x, vp.y);
        //SDL_RenderSetViewport(renderer, &vp);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);
    }
}
