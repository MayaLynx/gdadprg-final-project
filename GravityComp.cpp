#include "GravityComp.h"

GravityComp::GravityComp(float gravityStrength, float maxFallSpeed)
    : Component("GravityComp")
{
    this->gravityStrength = gravityStrength;
    this->maxFallSpeed = maxFallSpeed;
}

void GravityComp::perform(sf::Time deltaTime)
{
    ModularGameObject* entity = getOwner();

    float velocityY = entity->getVerticalVelocity();

    // This makes the downward speed increase over time.
    velocityY += gravityStrength * deltaTime.asSeconds();

    // This limits the fall speed so it does not get too high.
    if(velocityY > maxFallSpeed)
        velocityY = maxFallSpeed;

    entity->setVerticalVelocity(velocityY);

    // This applies the updated vertical speed to the sprite.
    // Collision still fixes the final position if the player lands on a platform.
    entity->getSprite()->move({0.f, velocityY * deltaTime.asSeconds()});
}
