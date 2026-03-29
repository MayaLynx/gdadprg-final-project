#pragma once

#include "Component.h"
#include "GameObject.h"
#include <vector>

class GameData
{
public:
    static GameData* createInstance();
    int getStage();
    void setStage(int val);
    int getLives();
    void setLives(int val);

    void addSnapshot(GameObject* obj);
    void clearSnapshot();
    std::vector<GameObject*> getSnapshot();
private:
    static GameData* myInstance;
    int stage;
    int lives;
    std::vector<GameObject*> snapshot;
    GameData();
};