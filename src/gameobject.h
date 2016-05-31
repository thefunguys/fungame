#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "sfml.h"
#include "boundary.h"


class GameObject {
  public:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Shader* shader;
    /*   7 0 1
     *  6     2
     *   5 4 3 */
    int direction;
    pVector pos;
    sf::Vector2i windowPos(sf::RenderTarget&);

    std::string name;
    bool focused;
    bool shadowcasts;
    // where we start to count for collisions
    Boundary boundary;

    pVector vel;
    pVector lastDir;
    int w, h, l;

    // pw and ph represent the width and height of objects in the collision system
    double pw, ph;
    double mass;

    virtual void render(sf::RenderTarget&, bool shadered = true);
    virtual void update(double dt);
    //bool collide(double, double, GameObject*);

    GameObject(std::string, int, int, int, int, int, int);
};

sf::Vector2i wpos(sf::RenderTarget& window, float x, float y);
sf::Vector2f wpos(sf::RenderTarget& window, sf::Vector2f v);

sf::Vector2f gpos(sf::RenderTarget& window, int x, int y);


#endif
