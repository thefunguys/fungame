#include <iostream>
#include <cstdlib>
#include <ctime>
#include <IL/il.h>
#include <IL/ilu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "game.h"
#include "keymap.h"
#include "player.h"
#include "sprite.h"
#include "LUtil.h"

using namespace std;

World* Game::current_world;

Game::Game(int w, int h) {
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to init SDL: " << SDL_GetError() << endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    window = SDL_CreateWindow("super cool game", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return;
    }

    glContext = SDL_GL_CreateContext(window);

    if (!initGL()) {
        cerr << "Failed to init gl" << endl;
        return;
    }
/*
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        return;
    }
*/

    world = new World("levels/test.lvl", renderer);
    surface = SDL_GetWindowSurface(window);
    current_world = world;
    cout << "game init finished" << endl;
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
    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
}

void Game::loop() {
    bool running = true;
    SDL_Event e;
    // in this loop we handle input, process events, draw all things, update
    // the window, and wait until the next frame

    int vx, vy;
    int lastupdate = SDL_GetTicks();
    Player* blackguy = world->cur_player;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                cout << "Received exit signal" << endl;
            } else if (e.type == SDL_KEYDOWN) {
                Keymap::keymap[e.key.keysym.sym] = 1;
            } else if (e.type == SDL_KEYUP) {
                Keymap::keymap[e.key.keysym.sym] = 0;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        world->update((SDL_GetTicks() - lastupdate) * 0.001);
        lastupdate = SDL_GetTicks();
        vx = 320 - blackguy->pos.x;
        vy = 240 - blackguy->pos.y;
        world->render(vx, vy);
        SDL_GL_SwapWindow(window);
        SDL_Delay(1000 / FPS);
    }
}
