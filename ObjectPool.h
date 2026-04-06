#pragma once

#include "GameObject.h"
#include <vector>

class ObjectPool
{
public:
    ObjectPool();
    ~ObjectPool();

    void initializeCollectibles(int count, float width, float height);
    GameObject* acquireCollectible();
    void releaseCollectible(GameObject* obj);
    void releaseAll();
    bool isManaged(GameObject* obj) const;

private:
    std::vector<GameObject*> available;
    std::vector<GameObject*> inUse;
};
