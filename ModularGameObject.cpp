#include "ModularGameObject.h"

ModularGameObject::ModularGameObject(std::string name, std::string texture, float width, float height)
    : GameObject(name, texture, width, height)
{
    moveDirection = 0;
    moveSpeed = 0.f;

    verticalVelocity = 0.f;
    grounded = false;
    jumpRequested = false;
}

ModularGameObject::~ModularGameObject()
{
    for(Component* cmp : componentList)
    {
        delete cmp;
    }
}

void ModularGameObject::attachComponent(Component* component)
{
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
    jumpRequested = true;
}

bool ModularGameObject::consumeJumpRequest()
{
    bool result = jumpRequested;
    jumpRequested = false;
    return result;
}

//until here

void ModularGameObject::init()
{
    
}

void ModularGameObject::update(sf::Time deltaTime)
{
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