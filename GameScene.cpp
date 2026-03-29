#include "GameScene.h"

GameScene::GameScene() : Scene("GameScene")
{

}

void GameScene::onLoad()
{
    GameData* gameData = GameData::createInstance();
    std::vector<GameObject*> snapshot = gameData->getSnapshot();

    if(snapshot.empty())
    {
        stage = 1;
        lives = 3;

        ModularGameObject* player = GameCharFactory::makePlayer("player", 33, 32);
        addObject(player);

        for(GameObject* obj : getAllObjects())
        {
            obj->init();
        }
    }
    else
    {
        for(GameObject* obj : snapshot)
        {
            addObject(obj);
        }
        gameData->clearSnapshot();
    }
}

void GameScene::onUnload()
{
    GameData* gameData = GameData::createInstance();
    
    for(GameObject* obj : getAllObjects())
    {
        gameData->addSnapshot(obj);
    }
    removeAllObjects();

    gameData->setStage(stage);
    gameData->setLives(lives);
}

void GameScene::update(sf::Time deltaTime)
{
    ModularGameObject* player = (ModularGameObject*)findObject("player");

    player->update(deltaTime);
}

void GameScene::keyPressTrigger(sf::Keyboard::Scan keyCode)
{
    ModularGameObject* player = (ModularGameObject*)findObject("player");

    if(keyCode == sf::Keyboard::Scan::Left)
    {
        player->setMoveDirection(LEFT);
    }
    else if(keyCode == sf::Keyboard::Scan::Right)
    {
        player->setMoveDirection(RIGHT);
    }
}

void GameScene::keyReleaseTrigger(sf::Keyboard::Scan keyCode)
{
    ModularGameObject* player = (ModularGameObject*)findObject("player");

    if(keyCode == sf::Keyboard::Scan::Left ||
        keyCode == sf::Keyboard::Scan::Right)
        {
            player->setMoveDirection(STOPPED);
        }
}