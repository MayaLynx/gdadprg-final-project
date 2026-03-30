#pragma once

#include "ModularGameObject.h"
#include "Component.h"
#include <SFML/Graphics.hpp>

class GravityComp : public Component
{
private:
    
    // How strongly gravity pulls downward every frame.
    float gravityStrength;

    // Keeps falling speed from becoming too large.
    float maxFallSpeed;

public:
    GravityComp(float gravityStrength, float maxFallSpeed);
    void perform(sf::Time deltaTime) override;
};