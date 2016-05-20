#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "sfml.h"
#include "boundary.h"


class GameObject {
  public:
    sf::Texture texture;
    sf::Sprite sprite;
    /*   7 0 1
     *  6     2
     *   5 4 3 */
    int direction;
    pVector pos;
    // where we start to count for collisions
    Boundary boundary;

    pVector vel;
    int w, h, l;

    // pw and ph represent the width and height of objects in the collision system

    double mass;
    sf::Shader shader;

    virtual void render(sf::RenderWindow&, bool shadered = true);
    virtual void update(double dt);
    //bool collide(double, double, GameObject*);

    GameObject(std::string, int, int, int, int, int);
};

#endif
