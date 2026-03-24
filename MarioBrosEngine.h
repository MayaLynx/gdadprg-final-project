#pragma once

#include "SceneManager.h"
#include <SFML/Graphics.hpp>

class MarioBrosEngine
{
private:
        sf::RenderWindow window;
        const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
        SceneManager* sceneMngr;
public:
        void init();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow *window);
        void keyPressTrigger(sf::Keyboard::Scan keyCode);
        void keyReleaseTrigger(sf::Keyboard::Scan keyCode);
        void run(std::string title, unsigned int width, unsigned int height);
        SceneManager* getSceneManager();
};