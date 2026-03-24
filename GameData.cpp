#include "GameData.h"

GameData* GameData::myInstance = nullptr;

GameData* GameData::createInstance()
{
    if(myInstance == nullptr)
    {
        myInstance = new GameData();
    }
    return myInstance;
}

int GameData::getLevel()
{
    return level;
}

void GameData::setLevel(int val)
{
    level = val;
}

int GameData::getLives()
{
    return lives;
}

void GameData::setLives(int val)
{
    lives = val;
}

void GameData::addSnapshot(GameObject* obj)
{
    snapshot.push_back(obj);
}

void GameData::clearSnapshot()
{
    snapshot.clear();
}

std::vector<GameObject*> GameData::getSnapshot()
{
    return snapshot;
}