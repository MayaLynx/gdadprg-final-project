#include "GameObject.h"

GameObject::GameObject(std::string name, std::string texture, float size)
    : name{name}
    , sideSize{size}
{

}

GameObject::~GameObject()
{
    delete sprite;
}

void GameObject::init(){}

std::string GameObject::getName()
{
    return name;
}

sf::Sprite* GameObject::getSprite()
{
    return sprite;
}

// Position Functions //
void GameObject::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;

    sprite->setPosition({sideSize*(x+0.5f), sideSize*(y+0.5f)});
}

int GameObject::getXPos()
{
    return x;
}

int GameObject::getYPos()
{
    return y;
}

void GameObject::update(sf::Time deltaTime){}

void GameObject::draw(sf::RenderWindow *window)
{
    window->draw(*sprite);
}