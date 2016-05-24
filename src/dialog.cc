#include <stdio.h>
#include <string>
#include "fns.h"
#include "sfml.h"
#include "dialog.h"
#include "game.h"


sf::Text Dialog::text;
std::vector<std::string> Dialog::dialog;
size_t Dialog::cur_dialog = 0;
sf::Thread* Dialog::thread = nullptr;

void Dialog::setDialog(std::string diag) {
    dialog.erase(dialog.begin(), dialog.end());
    std::string* tmp = new std::string;
    for (size_t i = 0; i < diag.length(); ++i) {
        if (i >= 156) {
            dialog.push_back(*tmp);
            delete tmp;
            tmp = new std::string;
        } else if (i > 0 && i % 78 == 0) {
            tmp->push_back('\n');
        }
        tmp->push_back(diag[i]);
    }
    dialog.push_back(*tmp);
    delete tmp;
    if (thread != nullptr) {
        thread->terminate();
    }
    delete thread;
    thread = new sf::Thread(&timeoutClear);
    thread->launch();
}

void Dialog::print() {
    if (dialog.size() == 0) {
        return;
    }
    text.setString(dialog[cur_dialog]);
    text.setCharacterSize(14);
    text.setPosition(Game::p->pos.x - GAME_WIDTH / 2 + 16 + 14, Game::p->pos.y + GAME_HEIGHT / 2 + 16 - 50);
    Game::cur_window->draw(text);
}

void Dialog::printNext() {
    if (dialog.size() > cur_dialog + 1) {
        cur_dialog++;
    }
}

void Dialog::initText() {
    sf::Font* font = new sf::Font;
    if (!font->loadFromFile("fonts/DejaVuSansMono.ttf")) {
        printf("failed to load font\n");
    }
    text.setFont(*font);
    text.setColor(sf::Color(0x90, 0xa0, 0xb0, 0xff));
}

void Dialog::timeoutClear() {
    //sf::Thread* thref = thread;
    sf::sleep(sf::milliseconds(5000));
    dialog.erase(dialog.begin(), dialog.end());
    // cry evry tim
    //delete thref;
}
