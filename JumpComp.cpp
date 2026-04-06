#include "JumpComp.h"

JumpComp::JumpComp(float jumpStrength)
    : Component("JumpComp")
{
    this->jumpStrength = jumpStrength;
}

void JumpComp::perform(sf::Time deltaTime)
{
    (void)deltaTime;

    ModularGameObject* entity = getOwner();

    //This only jumps if jump was requested and player is on the ground.
    // I kept this check here so the input does not force a jump in mid-air.
    if(entity->consumeJumpRequest() && entity->isGrounded())
    {
        // This uses the jump strength from the factory so the jump is easier to tune.
        entity->setVerticalVelocity(-jumpStrength);
        entity->setGrounded(false);
    }
}
