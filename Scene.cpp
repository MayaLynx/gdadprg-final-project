#include "Scene.h"

Scene::Scene(std::string name)
    : name{name}
{}

Scene::~Scene()
{
    for(GameObject* obj : objects)
    {
        delete obj;
    }
}

std::string Scene::getName()
{
    return name;
}

void Scene::update(sf::Time deltaTime)
{
    for(GameObject* obj : objects)
    {
        obj->update(deltaTime);
    }
}

void Scene::draw(sf::RenderWindow* window)
{
    for(GameObject* obj : objects)
    {
        obj->draw(window);
    }
}

void Scene::addObject(GameObject* obj)
{
    objects.push_back(obj);
}

GameObject* Scene::findObject(std::string id)
{
    for(GameObject* obj : objects)
    {
        if(obj->getName() == id)
        {
            return obj;
        }
    }
    return nullptr;
}

std::vector<GameObject*> Scene::getAllObjects()
{
    return objects;
}

void Scene::removeObject(std::string id)
{
    GameObject* obj = findObject(id);
    removeObject(obj);
}

void Scene::removeObject(GameObject *obj)
{
    objects.erase(std::find(objects.begin(), objects.end(), obj));
}

void Scene::removeAllObjects()
{
    objects.clear();
}