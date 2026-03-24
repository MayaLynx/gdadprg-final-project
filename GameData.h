#pragma once

#include "Component.h"
#include "GameObject.h"
#include <vector>

class GameData
{
public:
    static GameData* createInstance();
    int getLevel();
    void setLevel(int val);
    int getLives();
    void setLives(int val);

    void addSnapshot(GameObject* obj);
    void clearSnapshot();
    std::vector<GameObject*> getSnapshot();
private:
    static GameData* myInstance;
    int level;
    int lives;
    std::vector<GameObject*> snapshot;
    GameData();
};