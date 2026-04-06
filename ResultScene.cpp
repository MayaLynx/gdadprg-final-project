#include "ResultScene.h"
#include "GameResource.h"
#include "SceneManager.h"

ResultScene::ResultScene()
    : Scene("ResultScene")
{
    GameResource* resource = GameResource::createInstance();

    panel.setSize({500.f, 500.f});
    panel.setFillColor(sf::Color(20, 24, 32));

    titleText = new sf::Text(*resource->getFont());
    titleText->setCharacterSize(38);
    titleText->setFillColor(sf::Color::White);

    summaryText = new sf::Text(*resource->getFont());
    summaryText->setCharacterSize(22);
    summaryText->setFillColor(sf::Color::White);

    restartButton = new Button("restartButton", "Restart");
    restartButton->setSize(220.f, 52.f);
    restartButton->setPosition(140.f, 300.f);

    quitButton = new Button("quitButton", "Quit");
    quitButton->setSize(220.f, 52.f);
    quitButton->setPosition(140.f, 370.f);

    selectedIndex = 0;
}

ResultScene::~ResultScene()
{
    delete titleText;
    delete summaryText;
    delete restartButton;
    delete quitButton;
}

void ResultScene::onLoad()
{
    GameData* data = GameData::createInstance();

    titleText->setString(data->getResultMessage());
    titleText->setPosition({70.f, 80.f});

    summaryText->setString(
        "Stage Reached: " + std::to_string(data->getStage()) +
        "\nScore: " + std::to_string(data->getScore()) +
        "\nTime: " + std::to_string(static_cast<int>(data->getElapsedTime())) + "s");
    summaryText->setPosition({110.f, 160.f});

    selectedIndex = 0;
    refreshSelection();
}

void ResultScene::update(sf::Time deltaTime)
{
    restartButton->update(deltaTime);
    quitButton->update(deltaTime);
}

void ResultScene::draw(sf::RenderWindow* window)
{
    window->draw(panel);
    window->draw(*titleText);
    window->draw(*summaryText);
    restartButton->draw(window);
    quitButton->draw(window);
}

void ResultScene::onUnload(){}

void ResultScene::keyPressTrigger(sf::Keyboard::Scan keyCode)
{
    if(keyCode == sf::Keyboard::Scan::Up || keyCode == sf::Keyboard::Scan::W)
    {
        selectedIndex = 0;
        refreshSelection();
    }
    else if(keyCode == sf::Keyboard::Scan::Down || keyCode == sf::Keyboard::Scan::S)
    {
        selectedIndex = 1;
        refreshSelection();
    }
    else if(keyCode == sf::Keyboard::Scan::Enter ||
            keyCode == sf::Keyboard::Scan::Space ||
            keyCode == sf::Keyboard::Scan::Z)
    {
        activateSelection();
    }
}

void ResultScene::keyReleaseTrigger(sf::Keyboard::Scan keyCode)
{
    (void)keyCode;
}

void ResultScene::refreshSelection()
{
    if(restartButton->isSelected()) restartButton->toggleSelected();
    if(quitButton->isSelected()) quitButton->toggleSelected();

    if(selectedIndex == 0)
    {
        restartButton->toggleSelected();
    }
    else
    {
        quitButton->toggleSelected();
    }
}

void ResultScene::activateSelection()
{
    if(selectedIndex == 0)
    {
        GameData::createInstance()->resetRun();
        SceneManager::createInstance()->loadScene("GameScene");
    }
    else
    {
        GameData::createInstance()->setShouldQuit(true);
    }
}
