#pragma once

#include "Scene.h"
#include "Button.h"
#include "GameData.h"
#include <SFML/Graphics.hpp>

class ResultScene : public Scene
{
public:
    ResultScene();
    ~ResultScene();

    void onLoad() override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow* window) override;
    void onUnload() override;

    void keyPressTrigger(sf::Keyboard::Scan keyCode);
    void keyReleaseTrigger(sf::Keyboard::Scan keyCode);

private:
    sf::RectangleShape panel;
    sf::Text* titleText;
    sf::Text* summaryText;
    Button* restartButton;
    Button* quitButton;
    int selectedIndex;

    void refreshSelection();
    void activateSelection();
};
