#pragma once

class Component;

#include "GameObject.h"
#include "Component.h"
#include <string>
#include <vector>
#include <iostream>

class ModularGameObject : public GameObject
{
private:
    std::vector<Component*> componentList;
    int moveDirection;
    float moveSpeed;

    // Added only what jump/gravity need.
    float verticalVelocity;
    bool grounded;
    bool jumpRequested;

public:
    ModularGameObject(std::string name, std::string texture, float width, float height);
    ~ModularGameObject();
    void attachComponent(Component* component);
    Component* getComponent(std::string componentName);
    void listComponents();

    int getMoveDirection();
    void setMoveDirection(int dir);
    float getMoveSpeed();
    void setMoveSpeed(float speed);

    float getVerticalVelocity();
    void setVerticalVelocity(float value);

    bool isGrounded();
    void setGrounded(bool value);

    void requestJump();
    bool consumeJumpRequest();

    void update(sf::Time deltaTime);
};