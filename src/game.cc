#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sfml.h"
#include "game.h"
#include "keymap.h"
#include "player.h"
#include "sprite.h"
#include "dialog.h"
#include "fns.h"
#include "music.h"

using namespace std;

World* Game::current_world;
Player* Game::p;
sf::RenderWindow* Game::cur_window;

Game::Game(int w, int h):
    window(sf::VideoMode(w, h), "game", sf::Style::Fullscreen & 0) {
    cur_window = &window;
    srand(time(NULL));
    dbpf("creating world...\n");
    world = new World("levels/test.lvl");
    current_world = world;
    Dialog::initText();
    if (!sf::Shader::isAvailable()) {
        cout << "SHADERS AREN'T HERE" << endl;
        exit(1);
    }
    dbpf("game init finished.\n");
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
    Player* blackguy = world->cur_player;
    play("assets/song.ogg");
    p = blackguy;
    sf::View view(sf::FloatRect(0.0f, 0.0f, GAME_WIDTH, GAME_HEIGHT));
    window.setView(view);
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
                dbpf("Received exit signal\n");
            }
        }

        double dt = clock.getElapsedTime().asSeconds();
        world->update(dt);
        view.setCenter(blackguy->pos.x + 16, blackguy->pos.y + 16);
        window.setView(view);
        window.clear();
        world->render(window);
        window.setView(view);
        Dialog::print();
        window.display();
        dts++;
        dttot += dt;
        clock.restart();
        sf::sleep(sf::seconds(1.0 / FPS - dt));
    }
    dbpf("avg dt: %.6f\n", dttot / dts);
    dbpf("total updates: %d\n", dts);
}
