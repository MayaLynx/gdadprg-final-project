#pragma once

#include "ModularGameObject.h"
#include "Component.h"
#include <SFML/Graphics.hpp>

class MoveComp : public Component
{
private:
    enum Direction{LEFT, RIGHT};
public:
    MoveComp(float moveSpeed);
    void perform(sf::Time deltaTime) override;
};