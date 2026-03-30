#include "PauseMenuScene.h"

PauseMenuScene::PauseMenuScene() : Scene("PauseMenuScene"){}

void PauseMenuScene::onLoad()
{
    addObject(new Background("pause_bg", "background", 500.f, 500.f));

    Button* exitButton = new Button("exitButton", "Exit");
    exitButton->setPosition(50.f, 50.f);
    exitButton->setSize(150.f, 50.f);
    selected = 0;
    exitButton->toggleSelected();

    addObject(exitButton);
}

void PauseMenuScene::onUnload()
{
    for(GameObject* obj: getAllObjects())
    {
        delete obj;
    }
    removeAllObjects();
}

void PauseMenuScene::keyPressTrigger(sf::Keyboard::Scan keyCode)
{
    if(keyCode == sf::Keyboard::Scan::Escape)
    {
        SceneManager* sceneMngr = SceneManager::createInstance();
        sceneMngr->loadScene("GameScene");
    }
    else if(keyCode == sf::Keyboard::Scan::Z)
    {
        if(selected == 0)
        {
            //SceneManager* sceneMngr = SceneManager::createInstance();
            std::cout << "Exit" << std::endl;
        }
    }
}

void PauseMenuScene::keyReleaseTrigger(sf::Keyboard::Scan keyCode){}