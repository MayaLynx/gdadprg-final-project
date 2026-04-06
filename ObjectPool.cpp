#include "ObjectPool.h"
#include "GameCharFactory.h"
#include <algorithm>

ObjectPool::ObjectPool(){}

ObjectPool::~ObjectPool()
{
    // The pool still owns every object here, so it cleans them all up at the end.
    for(GameObject* obj : available)
    {
        delete obj;
    }

    for(GameObject* obj : inUse)
    {
        delete obj;
    }
}

void ObjectPool::initializeCollectibles(int count, float width, float height)
{
    // This creates a reusable set of collectibles first.
    // That way the game does not keep creating and destroying them during play.
    if(!available.empty() || !inUse.empty())
    {
        return;
    }

    for(int i = 0; i < count; ++i)
    {
        available.push_back(GameCharFactory::makeCollectible(
            "collectible_" + std::to_string(i), 0, 0, width, height));
    }
}

GameObject* ObjectPool::acquireCollectible()
{
    // This gets one free collectible from the pool.
    if(available.empty())
    {
        return nullptr;
    }

    GameObject* obj = available.back();
    available.pop_back();
    inUse.push_back(obj);
    return obj;
}

void ObjectPool::releaseCollectible(GameObject* obj)
{
    // This returns the collectible back to the pool after use.
    auto it = std::find(inUse.begin(), inUse.end(), obj);
    if(it == inUse.end())
    {
        return;
    }

    available.push_back(obj);
    inUse.erase(it);
}

void ObjectPool::releaseAll()
{
    // This is just a quick reset helper for the whole pool.
    while(!inUse.empty())
    {
        GameObject* obj = inUse.back();
        inUse.pop_back();
        available.push_back(obj);
    }
}

bool ObjectPool::isManaged(GameObject* obj) const
{
    // This checks if an object belongs to the pool or not.
    return std::find(available.begin(), available.end(), obj) != available.end() ||
           std::find(inUse.begin(), inUse.end(), obj) != inUse.end();
}
