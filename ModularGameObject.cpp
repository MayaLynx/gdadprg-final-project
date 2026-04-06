#include "ModularGameObject.h"

ModularGameObject::ModularGameObject(std::string name, std::string texture, float width, float height)
    : GameObject(name, texture, width, height)
{
    moveDirection = 0;
    moveSpeed = 0.f;

    // These are the extra values used by the movement, jump, and gravity components.
    verticalVelocity = 0.f;
    grounded = false;
    jumpRequested = false;
}

ModularGameObject::~ModularGameObject()
{
    // This object owns its components, so it deletes them here.
    for(Component* cmp : componentList)
    {
        delete cmp;
    }
}

void ModularGameObject::attachComponent(Component* component)
{
    // This attaches a component to the object.
    // So behavior gets added piece by piece instead of being hardcoded in one class.
    componentList.push_back(component);
    component->attachOwner(this);
}

int ModularGameObject::getMoveDirection()
{
    return moveDirection;
}

void ModularGameObject::setMoveDirection(int dir)
{
    moveDirection = dir;
}

float ModularGameObject::getMoveSpeed()
{
    return moveSpeed;
}

void ModularGameObject::setMoveSpeed(float speed)
{
    moveSpeed = speed;
}

//Enzo changes

float ModularGameObject::getVerticalVelocity()
{
    return verticalVelocity;
}

void ModularGameObject::setVerticalVelocity(float value)
{
    verticalVelocity = value;
}

bool ModularGameObject::isGrounded()
{
    return grounded;
}

void ModularGameObject::setGrounded(bool value)
{
    grounded = value;
}

void ModularGameObject::requestJump()
{
    // I separated the jump request from the actual jump itself.
    // So input asks for it first, then JumpComp decides if it is valid.
    jumpRequested = true;
}

bool ModularGameObject::consumeJumpRequest()
{
    bool result = jumpRequested;
    jumpRequested = false;
    return result;
}

//until here

void ModularGameObject::update(sf::Time deltaTime)
{
    // This lets every attached component do its own job each frame.
    for(Component* cmp : componentList)
    {
        cmp->perform(deltaTime);
    }
}

void ModularGameObject::listComponents()
{
    for(Component* cmp : componentList)
    {
        std::cout << cmp->getName() << std::endl;
    }
}
