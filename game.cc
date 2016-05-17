#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sfml.h"
#include "game.h"
#include "keymap.h"
#include "player.h"
#include "sprite.h"

using namespace std;

World* Game::current_world;

Game::Game(int w, int h): window(sf::VideoMode(640, 480), "game") {
    srand(time(NULL));
    world = new World("levels/test.lvl");
    current_world = world;
    cout << "game init finished" << endl;
}

Game::~Game() {
}

void Game::loop() {
    // in this loop we handle input, process events, draw all things, update
    // the window, and wait until the next frame
    int dts = 0;
    double dttot = 0.0;

    window.setVerticalSyncEnabled(true);
    sf::Clock clock;
    int vx, vy;
    Player* blackguy = world->cur_player;
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
                cout << "Received exit signal" << endl;
            }
        }

        double dt = clock.getElapsedTime().asSeconds();
        world->update(dt);
        vx = 320 - blackguy->pos.x;
        vy = 240 - blackguy->pos.y;
        window.clear();
        world->render(window, vx, vy);
        window.display();
        dts++;
        dttot += dt;
        clock.restart();
        sf::sleep(sf::seconds(0.016667 - dt));
    }
    std::cout << "avg dt: " << dttot / dts << std::endl;
    std::cout << "total updates: " <<  dts << std::endl;
}
