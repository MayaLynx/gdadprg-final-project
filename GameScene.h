#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "GameData.h"
#include "GameCharFactory.h"

class GameScene : public Scene
{
private:
    int lives, stage;
    enum Direction{STOPPED, LEFT, RIGHT};
public:
    GameScene();
    void onLoad() override;
    void update(sf::Time deltaTime);
    void onUnload() override;
    void keyPressTrigger(sf::Keyboard::Scan keyCode);
    void keyReleaseTrigger(sf::Keyboard::Scan keyCode);
};