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
   
    // Gravity makes downward speed increase over time.
    velocityY += gravityStrength * deltaTime.asSeconds();

    // Limit fall speed so it does not get too high.
    if(velocityY > maxFallSpeed)
        velocityY = maxFallSpeed;

    
    entity->setVerticalVelocity(velocityY);

  
    entity->getSprite()->move({0.f, velocityY * deltaTime.asSeconds()});
}