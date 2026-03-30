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