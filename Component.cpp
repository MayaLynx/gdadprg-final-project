#include "Component.h"

Component::Component(std::string name)
    : name{name}
{

}

void Component::attachOwner(ModularGameObject* newOwner)
{
    owner = newOwner;
}

ModularGameObject* Component::getOwner()
{
    return owner;
}

std::string Component::getName()
{
    return name;
}

//////////// COMPONENTS ////////////
// Jump component //
class JumpComp : public Component
{
private:
    float jumpHeight;
    float jumpTime;
    sf::Time elapsedTime;
public:
    JumpComp(float jumpHeight)
        : Component("JumpComp")
        , jumpHeight{jumpHeight}
    {
        elapsedTime = sf::Time::Zero;
        jumpTime = 1.f;
    };

    void perform(sf::Time deltaTime) override
    {
        ModularGameObject* entity = getOwner();
        elapsedTime += deltaTime;
        
        if(elapsedTime.asSeconds() <= jumpTime)
        {
            entity->getSprite()->move({0.f, jumpHeight * (1.f / 60.f)});
        }
        else
        {
            elapsedTime = sf::Time::Zero;
        }
        
    }
};

// Gravity component //
class GravityComp : public Component
{
private:
    float gravStrength;
public:
    GravityComp()
        : Component("GravityComp")
    {}
    void perform(sf::Time deltaTime) override
    {
        ModularGameObject* entity = getOwner();
        
    }
};