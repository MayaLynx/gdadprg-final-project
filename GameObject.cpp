#include "GameObject.h"

GameObject::GameObject(std::string name, std::string texture, float width, float height)
    : name{name}
    , width{width}
    , height{height}
{
    GameResource* resource = GameResource::createInstance();
    sf::IntRect rect = (*resource->getAtlas())[texture];
    sprite = new sf::Sprite(*resource->getTexture(), rect);

    sprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});
    sprite->setScale({width/rect.size.x, height/rect.size.y});
    sprite->move({width/2, height/2});

    x = 0;
    y = 0;
}

GameObject::GameObject(std::string name)
    : name{name}
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

    sprite->setPosition({width*(x+0.5f), height*(y+0.5f)});
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