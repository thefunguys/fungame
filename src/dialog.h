#ifndef DIALOG_H
#define DIALOG_H
#include <vector>
#include "sfml.h"

class Dialog {
  public:
    static void print();
    static sf::Text text;
    static sf::Thread* thread;
    static void setDialog(std::string);
    static void initText();
    static std::vector<std::string> dialog;
    static void timeoutClear();
    static void printNext();
    static size_t cur_dialog;
};


#endif
