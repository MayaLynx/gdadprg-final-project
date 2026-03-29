#pragma once

#include "ModularGameObject.h"
#include "Component.h"
#include <SFML/Graphics.hpp>

class MoveComp : public Component
{
private:
    enum Direction{STOPPED, LEFT, RIGHT};
public:
    MoveComp();
    void perform(sf::Time deltaTime) override;
};