#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GameObject
{
private:
    std::string name;
    sf::Sprite* sprite;
    int x, y;
    float sideSize;

public:
    GameObject(std::string name, std::string texture, float size);
    ~GameObject();
    std::string getName();
    sf::Sprite* getSprite();

    void setPosition(int newX, int newY);
    int getXPos();
    int getYPos();

    void init();
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow *window);
};