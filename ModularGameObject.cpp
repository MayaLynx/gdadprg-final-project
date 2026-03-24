#include "ModularGameObject.h"

ModularGameObject::ModularGameObject(std::string name, std::string texture, float size)
    : GameObject(name, texture, size)
{
    
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