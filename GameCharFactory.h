#pragma once

#include "GameObject.h"
#include "ModularGameObject.h"
#include "Component.h"
#include "MoveComp.h"

class GameCharFactory
{
public:
    static ModularGameObject* makePlayer(std::string name, float width, float height);
    static GameObject* makeBlock(std::string name, int xPos, int yPos, float width, float height);
    static GameObject* makeGoal(std::string name, int xPos, int yPos, float width, float height);
    static GameObject* makeCollectible(std::string name, int xPos, int yPos, float width, float height);
};
