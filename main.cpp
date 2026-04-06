#include "SceneManager.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "GameData.h"
#include "GameResource.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>

int main()
{
    // made it so that Main handles the game loop directly
    sf::RenderWindow window(sf::VideoMode({500, 500}), "GDADPRG Platformer");
    window.setFramerateLimit(60);

    const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Clock clock;
    sf::Time timestamp = sf::Time::Zero;

    // This sets up the scenes once at the start.
    SceneManager* sceneMngr = SceneManager::createInstance();
    sceneMngr->registerScene(new GameScene());
    sceneMngr->registerScene(new ResultScene());
    sceneMngr->loadScene("GameScene");

    // This grabs the already loaded BGM buffer.
    GameResource* resource = GameResource::createInstance();
    sf::Sound bgm(*resource->getBgmBuffer());
    bgm.setLooping(true);
    bgm.setVolume(20.f);
    bgm.play();

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                // The current scene can change, so input gets forwarded to whichever scene is active right now.
                GameScene* game = dynamic_cast<GameScene*>(sceneMngr->getCurrentScene());
                if(game != nullptr)
                {
                    game->keyPressTrigger(keyPressed->scancode);
                }

                ResultScene* result = dynamic_cast<ResultScene*>(sceneMngr->getCurrentScene());
                if(result != nullptr)
                {
                    result->keyPressTrigger(keyPressed->scancode);
                }
            }
            else if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                GameScene* game = dynamic_cast<GameScene*>(sceneMngr->getCurrentScene());
                if(game != nullptr)
                {
                    game->keyReleaseTrigger(keyReleased->scancode);
                }

                ResultScene* result = dynamic_cast<ResultScene*>(sceneMngr->getCurrentScene());
                if(result != nullptr)
                {
                    result->keyReleaseTrigger(keyReleased->scancode);
                }
            }
        }

        // This lets the pause/result UI close the program cleanly.
        if(GameData::createInstance()->getShouldQuit())
        {
            window.close();
            continue;
        }

        timestamp += clock.restart();
        while(timestamp > TimePerFrame)
        {
            timestamp -= TimePerFrame;
            sceneMngr->updateCurrentScene(TimePerFrame);
        }

        window.clear(sf::Color(92, 148, 252));
        sceneMngr->drawCurrentScene(&window);
        window.display();
    }

    return 0;
}
