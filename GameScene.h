#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "GameData.h"
#include "GameCharFactory.h"
#include "Button.h"
#include "ObjectPool.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class GameScene : public Scene
{
private:
    int lives;
    int stage;

    enum Direction { STOPPED, LEFT, RIGHT };

    std::vector<GameObject*> solidBlocks;
    std::vector<GameObject*> activeCollectibles;
    ObjectPool collectiblePool;

    sf::View camera;
    float stageWidth;
    int spawnX;
    int spawnY;
    GameObject* goalDoor;
    bool poolReady;
    bool paused;

    sf::Sound* jumpSfx;
    sf::Text* hudText;
    sf::Text* pauseTitle;
    sf::Text* pauseHint;
    sf::RectangleShape pausePanel;
    Button* resumeButton;
    Button* quitButton;
    int pauseSelectedIndex;

    void clearLevelObjects();
    void buildCurrentLevel();
    void buildStageOne();
    void buildStageTwo();
    void buildStageThree();

    void addBlock(int x, int y, float width = 64.f, float height = 64.f);
    void addFloorRange(int startX, int endX, int y, float width = 64.f, float height = 64.f);
    void addGoal(int x, int y);
    void addCollectible(int x, int y);
    void spawnPlayer(int x, int y);
    void respawnPlayer();

    void handleCollisions(ModularGameObject* player);
    void updateCamera(ModularGameObject* player);
    void updateHud();
    void checkCollectibles(ModularGameObject* player);
    bool checkStageClear(ModularGameObject* player);
    void checkFailState(ModularGameObject* player);
    bool rectanglesOverlap(const sf::FloatRect& a, const sf::FloatRect& b);

    void refreshPauseSelection();
    void activatePauseSelection();

public:
    GameScene();
    ~GameScene();

    void onLoad() override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow* window) override;
    void onUnload() override;

    void keyPressTrigger(sf::Keyboard::Scan keyCode);
    void keyReleaseTrigger(sf::Keyboard::Scan keyCode);
};
