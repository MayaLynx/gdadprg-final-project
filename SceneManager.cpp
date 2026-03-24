#include "SceneManager.h"

SceneManager* SceneManager::myInstance = nullptr;

SceneManager* SceneManager::createInstance()
{
    if(myInstance==nullptr)
    {
        myInstance = new SceneManager();
    }
    return myInstance;
}

SceneManager::SceneManager()
{
    currentScene = nullptr;
}

SceneManager::~SceneManager()
{
    for(Scene* s : scenes)
    {
        delete s;
    }
}

Scene* SceneManager::findScene(std::string name)
{
    for(Scene* s : scenes)
    {
        if(s->getName() == name)
        {
            return s;
        }
    }
    return nullptr;
}

void SceneManager::registerScene(Scene* scene)
{
    scenes.push_back(scene);
}


Scene* SceneManager::loadScene(std::string id)
{
    if(currentScene != nullptr && currentScene->getName() == id)
    {
        return currentScene;
    }

    Scene* newCurrentScene = findScene(id);
    if(currentScene != nullptr)
    {
        currentScene->onUnload();
    }
    newCurrentScene->onLoad();
    currentScene = newCurrentScene;
    return newCurrentScene;
}

Scene* SceneManager::getCurrentScene()
{
    return currentScene;
}

void SceneManager::updateCurrentScene(sf::Time deltaTime)
{
    if(currentScene != nullptr)
    {
        currentScene->update(deltaTime);
    }
}

void SceneManager::drawCurrentScene(sf::RenderWindow *window)
{
    if(currentScene != nullptr)
    {
        currentScene->draw(window);
    }
}