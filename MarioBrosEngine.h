#pragma once

#include "SceneManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "PauseMenuScene.h"
#include "GameCharFactory.h"
#include <SFML/Graphics.hpp>

class MarioBrosEngine
{
private:
        sf::RenderWindow window;
        const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
        SceneManager* sceneMngr;
        int windowWidth = 500;
        int windowHeight = 500;
public:
        void init();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow *window);
        void keyPressTrigger(sf::Keyboard::Scan keyCode);
        void keyReleaseTrigger(sf::Keyboard::Scan keyCode);
        void run(std::string title, unsigned int width, unsigned int height);
        SceneManager* getSceneManager();
        int getWindowWidth();
        int getWindowHeight();
};