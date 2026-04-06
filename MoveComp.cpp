#include "MoveComp.h"

MoveComp::MoveComp()
    : Component("MoveComp")
{
}

void MoveComp::perform(sf::Time deltaTime)
{
    ModularGameObject* entity = getOwner();
    float moveSpeed = entity->getMoveSpeed();

    // This makes the horizontal movement time-based so it feels more consistent.
    float dx = moveSpeed * deltaTime.asSeconds();

    switch(entity->getMoveDirection())
    {
        case LEFT:
            entity->getSprite()->move({-dx, 0.f});
            break;

        case RIGHT:
            entity->getSprite()->move({dx, 0.f});
            break;
    }
}
