#include "MarioBrosEngine.h"


void MarioBrosEngine::init()
{
    sceneMngr = SceneManager::createInstance();
    sceneMngr->registerScene(new GameScene());
    sceneMngr->registerScene(new PauseMenuScene());
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

int MarioBrosEngine::getWindowWidth()
{
    return windowWidth;
}

int MarioBrosEngine::getWindowHeight()
{
    return windowHeight;
}

void MarioBrosEngine::keyPressTrigger(sf::Keyboard::Scan keyCode)
{
    SceneManager* sceneMngr = getSceneManager();
    GameScene* game = dynamic_cast<GameScene*>(sceneMngr->getCurrentScene());
    if(game != nullptr)
    {
        game->keyPressTrigger(keyCode);
    }

    PauseMenuScene* pauseMenu = dynamic_cast<PauseMenuScene*>(sceneMngr->getCurrentScene());
    if(pauseMenu != nullptr)
    {
        pauseMenu->keyPressTrigger(keyCode);
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

    PauseMenuScene* pauseMenu = dynamic_cast<PauseMenuScene*>(sceneMngr->getCurrentScene());
    if(pauseMenu != nullptr)
    {
        pauseMenu->keyReleaseTrigger(keyCode);
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