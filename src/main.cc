#include <iostream>
#include "game.h"

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char ** argv) {
    int exit_code = 0;
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.loop();
    return exit_code;
}

