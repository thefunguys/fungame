#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char ** argv) {
    int exit_code = 0;
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to init SDL: " << SDL_GetError() << endl;
        exit_code = -1;
        goto cleanup;
    }

    window = SDL_CreateWindow("super cool game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        exit_code = -1;
        goto cleanup;
    }

    screenSurface = SDL_GetWindowSurface(window);

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

cleanup:
    SDL_DestroyWindow(window);
    SDL_Quit();
    return exit_code;
}


