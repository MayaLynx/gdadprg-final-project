#include "MoveComp.h"

MoveComp::MoveComp(float moveSpeed)
    : Component("MoveComp")
{
    
}

void MoveComp::perform(sf::Time deltaTime)
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