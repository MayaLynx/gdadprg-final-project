#include "JumpComp.h"

JumpComp::JumpComp(float jumpStrength)
    : Component("JumpComp")
{
    this->jumpStrength = jumpStrength;
}

void JumpComp::perform(sf::Time deltaTime)
{
    ModularGameObject* entity = getOwner();

    // only jump if jump was requested and player is on the ground.
    if(entity->consumeJumpRequest() && entity->isGrounded())
    {
        entity->setVerticalVelocity(-500.f);
        entity->setGrounded(false);
    }
}