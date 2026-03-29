#include "MarioBrosEngine.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameCharFactory.h"

void MarioBrosEngine::init()
{
    sceneMngr = SceneManager::createInstance();
    sceneMngr->registerScene(new GameScene());
    sceneMngr->loadScene("GameScene");
}

void MarioBrosEngine::update(sf::Time deltaTime)
{
    sceneMngr->updateCurrentScene(deltaTime);
}

void MarioBrosEngine::draw(sf::RenderWindow *window)
{
    sceneMngr->drawCurrentScene(window);
}

SceneManager* MarioBrosEngine::getSceneManager()
{
    return sceneMngr;
}

void MarioBrosEngine::keyPressTrigger(sf::Keyboard::Scan keyCode)
{
    SceneManager* sceneMngr = getSceneManager();
    GameScene* game = dynamic_cast<GameScene*>(sceneMngr->getCurrentScene());
    if(game != nullptr)
    {
        game->keyPressTrigger(keyCode);
    }
}

void MarioBrosEngine::keyReleaseTrigger(sf::Keyboard::Scan keyCode)
{
    SceneManager* sceneMngr = getSceneManager();
    GameScene* game = dynamic_cast<GameScene*>(sceneMngr->getCurrentScene());
    if(game != nullptr)
    {
        game->keyReleaseTrigger(keyCode);
    }
}

void MarioBrosEngine::run(std::string title, unsigned int width, unsigned int height)
{
    window.create(sf::VideoMode({width, height}), title);
    window.setFramerateLimit(60);
    init();
    sf::Clock clock;
    sf::Time timestamp = sf::Time::Zero;
    while (window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                 window.close();
            else if(const auto* keyPressed=event->getIf<sf::Event::KeyPressed>())
                keyPressTrigger(keyPressed->scancode);
            else if(const auto* keyPressed=event->getIf<sf::Event::KeyReleased>())
                keyReleaseTrigger(keyPressed->scancode);
        }
        timestamp += clock.restart();
        while(timestamp>TimePerFrame)
        {
            timestamp -= TimePerFrame;
            update(TimePerFrame);
        }
        window.clear();
        draw(&window);
        window.display();
    }
}