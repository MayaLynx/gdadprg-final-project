#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "GameData.h"
#include "GameCharFactory.h"
#include "Background.h"
#include <vector>
#include <algorithm>

class GameScene : public Scene
{
private:
    int lives, stage;
    enum Direction{STOPPED, LEFT, RIGHT};

    
    // Added these for simple collision handling and camera follow.
    std::vector<GameObject*> solidBlocks;
    sf::View camera;
    float stageWidth;

    void buildSimpleStage();
    void handleCollisions(ModularGameObject* player);
    void updateCamera(ModularGameObject* player);
    bool rectanglesOverlap(const sf::FloatRect& a, const sf::FloatRect& b);

public:
    GameScene();
    void onLoad() override;
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow* window) override;
    void onUnload() override;
    void keyPressTrigger(sf::Keyboard::Scan keyCode);
    void keyReleaseTrigger(sf::Keyboard::Scan keyCode);
};