#pragma once



#include "MarioBrosEngine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"
#include "Background.h"
#include "GameData.h"
#include <SFML/Graphics.hpp>

class PauseMenuScene : public Scene
{
private:
    int selected;
public:
    PauseMenuScene();
    void onLoad() override;
    void onUnload() override;
    void keyPressTrigger(sf::Keyboard::Scan keyCode);
    void keyReleaseTrigger(sf::Keyboard::Scan keyCode);
};