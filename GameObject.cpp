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
    sprite = nullptr;
    x = 0;
    y = 0;
    width = 0.f;
    height = 0.f;
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

    if(sprite != nullptr)
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

sf::FloatRect GameObject::getBounds()
{
    // This gives the real rectangle of the sprite in the game.
    // I added this because MoveComp already moves the sprite directly,so collision should also use the sprite's actual bounds.
 


    if(sprite != nullptr)
        return sprite->getGlobalBounds();

    return sf::FloatRect();
}

sf::Vector2f GameObject::getWorldPosition()
{
    // Returns the sprite's actual position in the world.
    // Useful for camera follow.
    if(sprite != nullptr)
        return sprite->getPosition();

    return sf::Vector2f(0.f, 0.f);
}

void GameObject::setWorldPosition(float newX, float newY)
{
    // Lets collision correction place the object using exact pixel values.
    // Didbt change setPosition(int,int) grid setup
    if(sprite != nullptr)
        sprite->setPosition({newX, newY});
}

void GameObject::update(sf::Time deltaTime){}

void GameObject::draw(sf::RenderWindow *window)
{
    if(sprite != nullptr)
        window->draw(*sprite);
}