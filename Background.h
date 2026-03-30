#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Background : public GameObject
{
private:
    sf::Sprite *sprite;
    sf::Texture texture;
public:
    Background(std::string name, std::string texture, float width, float height);
    void init();
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow *window);
};