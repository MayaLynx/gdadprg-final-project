#include "Background.h"

Background::Background(std::string name, std::string texture, float width, float height)
    : GameObject(name, texture, width, height)
{

}

void Background::init()
{
    setPosition(0, 0);
}

void Background::update(sf::Time deltaTime){}

void Background::draw(sf::RenderWindow *window)
{
    window->draw(*sprite);
}
