#pragma once

#include <Scene.h>
#include <SFML/Graphics.hpp>
#include <vector>

class SceneManager
{
public:
    static SceneManager* createInstance();
    void registerScene(Scene* Scene);
    Scene* loadScene(std::string id);
    Scene* getCurrentScene();
    void updateCurrentScene(sf::Time deltaTime);
    void drawCurrentScene(sf::RenderWindow *window);
    ~SceneManager();
private:
    static SceneManager* myInstance;
    std::vector<Scene*> scenes;
    Scene* currentScene;
    SceneManager();
    Scene* findScene(std::string name);
};