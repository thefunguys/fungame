#ifndef KEYMAP_H
#define KEYMAP_H
#include <map>
#include <SDL2/SDL.h>

class Keymap {
public:
    static std::map<int, int> keymap;
    static std::map<int, int> init_map() {
        std::map<int, int> init;
        return init;
    }
};
#endif
