#pragma once

#include "ModularGameObject.h"
#include "Component.h"

class Player : public ModularGameObject
{
private:
    int direction;
public:
    Player(std::string id, float width, float height);
};