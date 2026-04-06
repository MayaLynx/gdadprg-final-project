#include "Button.h"

Button::Button(std::string name, std::string textVal)
    : GameObject(name)
{
    selected = false;
    elapsedTime = sf::Time::Zero;
    blinkTime = 0.5f;

    rec = new sf::RectangleShape();
    rec->setFillColor(sf::Color(245, 245, 245));
    rec->setOutlineColor(sf::Color::Black);
    rec->setOutlineThickness(4.f);

    GameResource* resource = GameResource::createInstance();
    text = new sf::Text(*resource->getFont());
    text->setString(textVal);
    text->setFillColor(sf::Color::Black);
    text->setCharacterSize(28);
}

Button::~Button()
{
    delete rec;
    delete text;
}

void Button::init(){}

void Button::update(sf::Time deltaTime)
{
    if(!selected)
    {
        return;
    }

    elapsedTime += deltaTime;
    if(elapsedTime.asSeconds() >= blinkTime)
    {
        elapsedTime = sf::Time::Zero;
        if(rec->getOutlineColor() == sf::Color::Yellow)
        {
            rec->setOutlineColor(sf::Color::Black);
        }
        else
        {
            rec->setOutlineColor(sf::Color::Yellow);
        }
    }
}

void Button::draw(sf::RenderWindow *window)
{
    window->draw(*rec);
    window->draw(*text);
}

void Button::setPosition(float x, float y)
{
    rec->setPosition({x, y});

    sf::FloatRect textBounds = text->getLocalBounds();
    sf::Vector2f size = rec->getSize();
    text->setPosition({x + (size.x - textBounds.size.x) / 2.f - textBounds.position.x,
                       y + (size.y - textBounds.size.y) / 2.f - textBounds.position.y - 2.f});
}

void Button::setSize(float width, float height)
{
    rec->setSize({width, height});
    sf::Vector2f pos = rec->getPosition();
    setPosition(pos.x, pos.y);
}

void Button::setText(std::string value)
{
    text->setString(value);
    sf::Vector2f pos = rec->getPosition();
    setPosition(pos.x, pos.y);
}

void Button::setBlinkTime(float blinkTime)
{
    this->blinkTime = blinkTime;
}

void Button::toggleSelected()
{
    selected = !selected;
    elapsedTime = sf::Time::Zero;
    if(selected)
    {
        rec->setOutlineColor(sf::Color::Yellow);
    }
    else
    {
        rec->setOutlineColor(sf::Color::Black);
    }
}

bool Button::isSelected()
{
    return selected;
}
