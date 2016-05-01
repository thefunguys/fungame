#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <map>

class GameObject {
    public:
    SDL_Texture* texture;
    std::map<std::string, SDL_Rect> surface_map;
/*   7 0 1
 *  6     2
 *   5 4 3 */
    int direction;
    double x;
    double y;
    // where we start to count for collisions
    double base_x_offset;
    double base_y_offset;
    
    double dx;
    double dy;
    int w;

    // pw and ph represent the width and height of objects in the collision system
    int pw;
    int h;
    int ph;

    double mass;

    // cx and cy calculate n + base_n_offset
    double cx(void);
    double cy(void);

    virtual void render(SDL_Renderer* renderer, int, int);
    virtual void update(double dt);
    bool collide(double, double, GameObject*);
    GameObject(std::string, SDL_Renderer*, int, int, int, int);
};

#endif
