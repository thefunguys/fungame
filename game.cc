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
Player* Game::p;

Game::Game(int w, int h): window(sf::VideoMode(640, 480), "game", sf::Style::Fullscreen & 0) {
    srand(time(NULL));
    world = new World("levels/test.lvl");
    current_world = world;
    cout << "game init finished" << endl;
    if (!sf::Shader::isAvailable()) {
        cout << "SHADERS AREN'T HERE" << endl;
        exit(1);
    }
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
    int vx = 0, vy = 0;
    Player* blackguy = world->cur_player;
    p = blackguy;
    sf::View view(sf::FloatRect(0.0f, 0.0f, 320.0f, 240.f));
    window.setView(view);
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
        view.setCenter(blackguy->pos.x, blackguy->pos.y);
        window.setView(view);
        window.clear(sf::Color(0x11, 0x11, 0x11));
        world->render(window, vx, vy);
        window.display();
        dts++;
        dttot += dt;
        clock.restart();
        sf::sleep(sf::seconds(1.0/FPS - dt));
    }
    std::cout << "avg dt: " << dttot / dts << std::endl;
    std::cout << "total updates: " <<  dts << std::endl;
}
