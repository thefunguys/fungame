#include <SDL2/SDL.h>
#include <iostream>
#include "game.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char ** argv) {
    int exit_code = 0;
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.loop();
    return exit_code;
}

