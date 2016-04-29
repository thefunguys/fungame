#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <map>

class GameObject {
    public:
    SDL_Texture* texture;
    std::map<std::string, SDL_Rect> surface_map;
    int x;
    int y;
    double dx;
    double dy;
    int w;
    int h;
    double mass;
    void render(SDL_Renderer* renderer);
    void update(double dt);
    GameObject(std::string, SDL_Renderer*, int, int, int, int);
};

#endif
