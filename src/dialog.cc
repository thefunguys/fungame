#include <stdio.h>
#include <string>
#include "fns.h"
#include "sfml.h"
#include "dialog.h"
#include "game.h"


sf::Text Dialog::text;
std::vector<std::string> Dialog::dialog;
sf::Thread* Dialog::thread = nullptr;

void Dialog::setDialog(std::string diag) {
    dialog.erase(dialog.begin(), dialog.end());
    std::string* tmp = new std::string;
    for (size_t i = 0; i < diag.length(); ++i) {
        if (i >= 80) {
            dialog.push_back(*tmp);
            delete tmp;
            tmp = new std::string;
        } else if (i > 0 && i % 40 == 0) {
        }
        tmp->push_back(diag[i]);
    }
    dialog.push_back(*tmp);
    delete tmp;
    if (thread != nullptr)
        thread->terminate();
    thread = new sf::Thread(&timeoutClear);
    thread->launch();
}

void Dialog::print() {
    if (dialog.size() == 0)
        return;
    text.setString(dialog[0]);
    text.setCharacterSize(14);
    text.setPosition(Game::p->pos.x - GAME_WIDTH/2 + 16, Game::p->pos.y + GAME_HEIGHT / 2 + 16 - 50);
    Game::cur_window->draw(text);
}

void Dialog::initText() {
    sf::Font* font = new sf::Font;
    if (!font->loadFromFile("fonts/DejaVuSansMono.ttf"))
        printf("failed to load font\n");
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
