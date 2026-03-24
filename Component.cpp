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
// Movement component //
class MoveComp : public Component
{
private:
    enum Direction{LEFT, RIGHT};
public:
    MoveComp(float moveSpeed)
        : Component("MoveComp")
    {};

    void perform(sf::Time deltaTime) override
    {
        ModularGameObject* entity = getOwner();
        float moveSpeed = entity->getMoveSpeed();
        switch(entity->getMoveDirection())
        {
            case LEFT:
                entity->getSprite()->move({-moveSpeed, 0.f});
                break;
            
            case RIGHT:
                entity->getSprite()->move({moveSpeed, 0.f});
                break;
        }
    }
};

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