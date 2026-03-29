#pragma once

class ModularGameObject;

#include "ModularGameObject.h"
#include <string>

class Component
{
private:
    std::string name;
    ModularGameObject* owner;
public:
    Component(std::string name);
    void attachOwner(ModularGameObject* owner);
    ModularGameObject* getOwner();
    std::string getName();
    virtual void perform(sf::Time deltaTime) = 0;
};