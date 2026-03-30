#pragma once

#include "GameObject.h"
#include "ModularGameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>

class Scene
{
private:
        std::string name;
        std::vector<GameObject*> objects;
public:
    Scene(std::string name);
    ~Scene();
    std::string getName();

    virtual void onLoad() = 0;
    virtual void update(sf::Time deltaTime);
    virtual void draw(sf::RenderWindow* window);
    virtual void onUnload() = 0;

    void addObject(GameObject* obj);
    GameObject* findObject(std::string id);
    std::vector<GameObject*> getAllObjects();
    void removeObject(std::string id);
    void removeObject(GameObject *obj);
    void removeAllObjects();
};