#pragma once

#include "ModularGameObject.h"
#include "Component.h"
#include <SFML/Graphics.hpp>

class JumpComp : public Component
{
private:
    float jumpStrength;

public:
    JumpComp(float jumpStrength);
    void perform(sf::Time deltaTime) override;
};