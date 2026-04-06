#include "GameScene.h"
#include "GameResource.h"
#include "ResultScene.h"
#include <algorithm>

GameScene::GameScene()
    : Scene("GameScene")
{
    GameResource* resource = GameResource::createInstance();

    lives = 3;
    stage = 1;
    stageWidth = 3200.f;
    spawnX = 1;
    spawnY = 4;
    goalDoor = nullptr;
    poolReady = false;
    paused = false;
    resumeButton = nullptr;
    quitButton = nullptr;
    pauseSelectedIndex = 0;

    camera.setSize({500.f, 500.f});
    camera.setCenter({250.f, 250.f});

    jumpSfx = new sf::Sound(*resource->getJumpBuffer());
    jumpSfx->setVolume(35.f);

    hudText = new sf::Text(*resource->getFont());
    hudText->setCharacterSize(20);
    hudText->setFillColor(sf::Color::White);
    hudText->setPosition({12.f, 10.f});

    pausePanel.setSize({320.f, 220.f});
    pausePanel.setPosition({90.f, 120.f});
    pausePanel.setFillColor(sf::Color(15, 20, 28, 220));
    pausePanel.setOutlineThickness(3.f);
    pausePanel.setOutlineColor(sf::Color::White);

    pauseTitle = new sf::Text(*resource->getFont());
    pauseTitle->setString("Paused");
    pauseTitle->setCharacterSize(34);
    pauseTitle->setFillColor(sf::Color::White);
    pauseTitle->setPosition({180.f, 145.f});

    pauseHint = new sf::Text(*resource->getFont());
    pauseHint->setString("Use W/S or Up/Down, then Enter/Z");
    pauseHint->setCharacterSize(18);
    pauseHint->setFillColor(sf::Color::White);
    pauseHint->setPosition({110.f, 305.f});

    resumeButton = new Button("resumeButton", "Resume");
    resumeButton->setSize(180.f, 46.f);
    resumeButton->setPosition(160.f, 205.f);

    quitButton = new Button("quitButton", "Quit Game");
    quitButton->setSize(180.f, 46.f);
    quitButton->setPosition(160.f, 265.f);
}

GameScene::~GameScene()
{
    clearLevelObjects();
    delete resumeButton;
    delete quitButton;
    delete jumpSfx;
    delete hudText;
    delete pauseTitle;
    delete pauseHint;
}

void GameScene::onLoad()
{
    GameData* data = GameData::createInstance();

    stage = data->getStage();
    lives = data->getLives();
    paused = false;
    pauseSelectedIndex = 0;
    refreshPauseSelection();

    if(!poolReady)
    {
        // This sets up the pooled collectibles once.
        collectiblePool.initializeCollectibles(20, 28.f, 28.f);
        poolReady = true;
    }

    buildCurrentLevel();
    updateHud();
}

void GameScene::update(sf::Time deltaTime)
{
    if(paused)
    {
        // While paused, only the pause menu keeps updating.
        resumeButton->update(deltaTime);
        quitButton->update(deltaTime);
        return;
    }

    GameData::createInstance()->addElapsedTime(deltaTime.asSeconds());

    ModularGameObject* player = static_cast<ModularGameObject*>(findObject("player"));
    if(player == nullptr)
    {
        return;
    }

    player->update(deltaTime);
    handleCollisions(player);
    updateCamera(player);
    checkCollectibles(player);
    if(checkStageClear(player))
    {
        return;
    }
    checkFailState(player);
    updateHud();
}

void GameScene::draw(sf::RenderWindow* window)
{
    window->setView(camera);
    Scene::draw(window);

    window->setView(window->getDefaultView());
    window->draw(*hudText);

    if(paused)
    {
        window->draw(pausePanel);
        window->draw(*pauseTitle);
        window->draw(*pauseHint);
        resumeButton->draw(window);
        quitButton->draw(window);
    }
}

void GameScene::onUnload()
{
    clearLevelObjects();
}

void GameScene::keyPressTrigger(sf::Keyboard::Scan keyCode)
{
    if(paused)
    {
        if(keyCode == sf::Keyboard::Scan::Escape)
        {
            paused = false;
            return;
        }

        if(keyCode == sf::Keyboard::Scan::Up || keyCode == sf::Keyboard::Scan::W)
        {
            pauseSelectedIndex = 0;
            refreshPauseSelection();
        }
        else if(keyCode == sf::Keyboard::Scan::Down || keyCode == sf::Keyboard::Scan::S)
        {
            pauseSelectedIndex = 1;
            refreshPauseSelection();
        }
        else if(keyCode == sf::Keyboard::Scan::Enter ||
                keyCode == sf::Keyboard::Scan::Space ||
                keyCode == sf::Keyboard::Scan::Z)
        {
            activatePauseSelection();
        }
        return;
    }

    ModularGameObject* player = static_cast<ModularGameObject*>(findObject("player"));
    if(player == nullptr)
    {
        return;
    }

    if(keyCode == sf::Keyboard::Scan::Escape)
    {
        paused = true;
        pauseSelectedIndex = 0;
        refreshPauseSelection();
        return;
    }

    if(keyCode == sf::Keyboard::Scan::Left || keyCode == sf::Keyboard::Scan::A)
    {
        player->setMoveDirection(LEFT);
    }
    else if(keyCode == sf::Keyboard::Scan::Right || keyCode == sf::Keyboard::Scan::D)
    {
        player->setMoveDirection(RIGHT);
    }
    else if(keyCode == sf::Keyboard::Scan::Space ||
            keyCode == sf::Keyboard::Scan::Up ||
            keyCode == sf::Keyboard::Scan::W ||
            keyCode == sf::Keyboard::Scan::Z)
    {
        if(player->isGrounded())
        {
            jumpSfx->play();
        }
        player->requestJump();
    }
}

void GameScene::keyReleaseTrigger(sf::Keyboard::Scan keyCode)
{
    if(paused)
    {
        return;
    }

    ModularGameObject* player = static_cast<ModularGameObject*>(findObject("player"));
    if(player == nullptr)
    {
        return;
    }

    if(keyCode == sf::Keyboard::Scan::Left || keyCode == sf::Keyboard::Scan::A ||
       keyCode == sf::Keyboard::Scan::Right || keyCode == sf::Keyboard::Scan::D)
    {
        player->setMoveDirection(STOPPED);
    }
}

void GameScene::clearLevelObjects()
{
    std::vector<GameObject*> currentObjects = getAllObjects();

    for(GameObject* obj : currentObjects)
    {
        if(collectiblePool.isManaged(obj))
        {
            collectiblePool.releaseCollectible(obj);
        }
        else
        {
            delete obj;
        }
    }

    removeAllObjects();
    activeCollectibles.clear();
    solidBlocks.clear();
    goalDoor = nullptr;
}

void GameScene::buildCurrentLevel()
{
    // This clears the old level objects first, then rebuilds the stage based on the current stage number.
    clearLevelObjects();

    switch(stage)
    {
        case 1:
            buildStageOne();
            break;
        case 2:
            buildStageTwo();
            break;
        default:
            buildStageThree();
            break;
    }

    for(GameObject* obj : getAllObjects())
    {
        obj->init();
    }

    respawnPlayer();
}

void GameScene::buildStageOne()
{
    // Stage 1 keeps the layout pretty simple.
    // It is mostly a gentle step-up stage so the player can get used to the movement first.
    stageWidth = 60.f * 64.f;

    addFloorRange(0, 59, 6);

    addFloorRange(8, 13, 5);
    addFloorRange(18, 22, 4);
    addFloorRange(28, 34, 5);
    addFloorRange(39, 45, 4);
    addFloorRange(50, 55, 3);

    // Small supports so the upper platforms do not look like they are just hanging there.
    addBlock(18, 5);
    addBlock(22, 5);
    addBlock(39, 5);
    addBlock(45, 5);
    addBlock(50, 4);
    addBlock(55, 4);
    addBlock(50, 5);
    addBlock(55, 5);

    spawnX = 2;
    spawnY = 4;
    spawnPlayer(spawnX, spawnY);

    addCollectible(10, 5);
    addCollectible(20, 4);
    addCollectible(31, 5);
    addCollectible(42, 4);
    addCollectible(53, 3);

    addGoal(58, 5);
}

void GameScene::buildStageTwo()
{
    // Stage 2 uses separated ground chunks and bridge-like platforms.
    // So this one feels different from Stage 1 right away.
    stageWidth = 72.f * 64.f;

    addFloorRange(0, 8, 6);
    addFloorRange(13, 22, 6);
    addFloorRange(27, 36, 6);
    addFloorRange(41, 50, 6);
    addFloorRange(55, 64, 6);
    addFloorRange(67, 71, 6);

    addFloorRange(9, 13, 4);
    addFloorRange(23, 28, 5);
    addFloorRange(37, 42, 3);
    addFloorRange(51, 56, 4);
    addFloorRange(62, 67, 5);

    // Supports / little towers so the higher bridges do not feel too random.
    addBlock(23, 6);
    addBlock(28, 6);
    addBlock(37, 4);
    addBlock(37, 5);
    addBlock(42, 4);
    addBlock(42, 5);
    addBlock(51, 5);
    addBlock(56, 5);

    spawnX = 2;
    spawnY = 4;
    spawnPlayer(spawnX, spawnY);

    addCollectible(11, 4);
    addCollectible(25, 5);
    addCollectible(39, 3);
    addCollectible(53, 4);
    addCollectible(64, 5);

    addGoal(69, 5);
}

void GameScene::buildStageThree()
{
    // Stage 3 is more of a climb stage.
    // It uses taller supported platforms so it does not just feel like another copy of the first two.
    stageWidth = 84.f * 64.f;

    addFloorRange(0, 83, 6);

    addFloorRange(10, 15, 5);
    addFloorRange(22, 28, 4);
    addFloorRange(36, 42, 3);
    addFloorRange(50, 56, 4);
    addFloorRange(64, 70, 5);
    addFloorRange(76, 81, 4);

    // Pillars / supports for the higher sections.
    addBlock(22, 5);
    addBlock(28, 5);
    addBlock(36, 4);
    addBlock(36, 5);
    addBlock(42, 4);
    addBlock(42, 5);
    addBlock(50, 5);
    addBlock(56, 5);
    addBlock(76, 5);
    addBlock(81, 5);

    spawnX = 2;
    spawnY = 4;
    spawnPlayer(spawnX, spawnY);

    addCollectible(12, 5);
    addCollectible(25, 4);
    addCollectible(39, 3);
    addCollectible(53, 4);
    addCollectible(67, 5);
    addCollectible(79, 4);

    addGoal(82, 5);
}

void GameScene::addBlock(int x, int y, float width, float height)
{
    GameObject* block = GameCharFactory::makeBlock(
        "block_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(static_cast<int>(solidBlocks.size())),
        x, y, width, height);
    addObject(block);
    solidBlocks.push_back(block);
}

void GameScene::addFloorRange(int startX, int endX, int y, float width, float height)
{
    for(int x = startX; x <= endX; ++x)
    {
        addBlock(x, y, width, height);
    }
}

void GameScene::addGoal(int x, int y)
{
    goalDoor = GameCharFactory::makeGoal("goal", x, y, 64.f, 96.f);
    addObject(goalDoor);
}

void GameScene::addCollectible(int x, int y)
{
    // This gets a collectible from the object pool instead of making a new one here.
    GameObject* collectible = collectiblePool.acquireCollectible();
    if(collectible == nullptr)
    {
        return;
    }

    // Here y is treated as the row of the block/platform under the collectible.
    // After placing it on that row, the sprite gets nudged up so it actually sits on top of the surface.
    collectible->setPosition(x, y);

    if(collectible->getSprite() != nullptr)
    {
        collectible->getSprite()->move({0.f, -46.f});
    }

    addObject(collectible);
    activeCollectibles.push_back(collectible);
}

void GameScene::spawnPlayer(int x, int y)
{
    ModularGameObject* player = GameCharFactory::makePlayer("player", 64.f, 64.f);
    player->setPosition(x, y);
    addObject(player);
}

void GameScene::respawnPlayer()
{
    ModularGameObject* player = static_cast<ModularGameObject*>(findObject("player"));
    if(player == nullptr)
    {
        return;
    }

    player->setPosition(spawnX, spawnY);
    player->setVerticalVelocity(0.f);
    player->setMoveDirection(STOPPED);
    player->setGrounded(false);
}

void GameScene::handleCollisions(ModularGameObject* player)
{
    // This handles the simple box collision for the platform blocks.
    sf::FloatRect playerBounds = player->getBounds();
    player->setGrounded(false);

    for(GameObject* block : solidBlocks)
    {
        sf::FloatRect blockBounds = block->getBounds();
        if(!rectanglesOverlap(playerBounds, blockBounds))
        {
            continue;
        }

        float playerLeft = playerBounds.position.x;
        float playerRight = playerBounds.position.x + playerBounds.size.x;
        float playerTop = playerBounds.position.y;
        float playerBottom = playerBounds.position.y + playerBounds.size.y;

        float blockLeft = blockBounds.position.x;
        float blockRight = blockBounds.position.x + blockBounds.size.x;
        float blockTop = blockBounds.position.y;
        float blockBottom = blockBounds.position.y + blockBounds.size.y;

        float overlapX = std::min(playerRight, blockRight) - std::max(playerLeft, blockLeft);
        float overlapY = std::min(playerBottom, blockBottom) - std::max(playerTop, blockTop);

        float playerCenterX = playerBounds.position.x + playerBounds.size.x / 2.f;
        float blockCenterX = blockBounds.position.x + blockBounds.size.x / 2.f;

        if(overlapX < overlapY)
        {
            // Using the centers works better here than using moveDirection.
            // It still pushes the player out even when the player is barely moving or not moving at all.
            if(playerCenterX < blockCenterX)
            {
                player->getSprite()->move({-overlapX, 0.f});
            }
            else
            {
                player->getSprite()->move({overlapX, 0.f});
            }
        }
        else
        {
            if(player->getVerticalVelocity() > 0)
            {
                // Landing on top of a block.
                player->getSprite()->move({0.f, -overlapY});
                player->setVerticalVelocity(0.f);
                player->setGrounded(true);
            }
            else if(player->getVerticalVelocity() < 0)
            {
                // Hitting the underside of a block.
                player->getSprite()->move({0.f, overlapY});
                player->setVerticalVelocity(0.f);
            }
        }

        playerBounds = player->getBounds();
    }
}

void GameScene::updateCamera(ModularGameObject* player)
{
    float halfWidth = camera.getSize().x / 2.f;
    float camX = player->getWorldPosition().x;

    if(camX < halfWidth)
    {
        camX = halfWidth;
    }

    if(camX > stageWidth - halfWidth)
    {
        camX = stageWidth - halfWidth;
    }

    camera.setCenter({camX, 250.f});
}

void GameScene::updateHud()
{
    // This updates the HUD text using the latest run data.
    GameData* data = GameData::createInstance();
    data->setStage(stage);
    data->setLives(lives);

    hudText->setString(
        "Stage: " + std::to_string(stage) +
        "   Lives: " + std::to_string(lives) +
        "   Score: " + std::to_string(data->getScore()) +
        "   Left: " + std::to_string(static_cast<int>(activeCollectibles.size())) +
        "   Time: " + std::to_string(static_cast<int>(data->getElapsedTime())) + "s");
}

void GameScene::checkCollectibles(ModularGameObject* player)
{
    std::vector<GameObject*> remaining;

    for(GameObject* collectible : activeCollectibles)
    {
        if(rectanglesOverlap(player->getBounds(), collectible->getBounds()))
        {
            // Once collected, this removes it from the scene and returns it to the pool.
            removeObject(collectible);
            collectiblePool.releaseCollectible(collectible);
            GameData::createInstance()->addScore(100);
        }
        else
        {
            remaining.push_back(collectible);
        }
    }

    activeCollectibles = remaining;
}

bool GameScene::checkStageClear(ModularGameObject* player)
{
    if(!activeCollectibles.empty())
    {
        return false;
    }

    bool reachedExit = false;

    // Keep the door collision, but also allow a clear when the player reaches the far right end.
    // This makes stage progression less picky in case the door sprite placement feels awkward.
    if(goalDoor != nullptr && rectanglesOverlap(player->getBounds(), goalDoor->getBounds()))
    {
        reachedExit = true;
    }

    if(player->getWorldPosition().x >= stageWidth - 96.f)
    {
        reachedExit = true;
    }

    if(!reachedExit)
    {
        return false;
    }

    if(stage < 3)
    {
        // This moves to the next stage using the same scene, just with a rebuilt layout.
        stage++;
        GameData::createInstance()->setStage(stage);
        buildCurrentLevel();
        updateHud();
    }
    else
    {
        GameData* data = GameData::createInstance();
        data->setResultMessage("You cleared all 3 levels!");
        SceneManager::createInstance()->loadScene("ResultScene");
    }

    return true;
}

void GameScene::checkFailState(ModularGameObject* player)
{
    // If the player falls too far below the level, this counts it as a failed attempt.
    if(player->getWorldPosition().y <= 650.f)
    {
        return;
    }

    lives--;
    GameData::createInstance()->setLives(lives);

    if(lives > 0)
    {
        respawnPlayer();
        updateHud();
        return;
    }

    GameData* data = GameData::createInstance();
    data->setResultMessage("Game Over");
    SceneManager::createInstance()->loadScene("ResultScene");
}

bool GameScene::rectanglesOverlap(const sf::FloatRect& a, const sf::FloatRect& b)
{
    return a.position.x < b.position.x + b.size.x &&
           a.position.x + a.size.x > b.position.x &&
           a.position.y < b.position.y + b.size.y &&
           a.position.y + a.size.y > b.position.y;
}

void GameScene::refreshPauseSelection()
{
    if(resumeButton->isSelected()) resumeButton->toggleSelected();
    if(quitButton->isSelected()) quitButton->toggleSelected();

    if(pauseSelectedIndex == 0)
    {
        resumeButton->toggleSelected();
    }
    else
    {
        quitButton->toggleSelected();
    }
}

void GameScene::activatePauseSelection()
{
    // The pause menu uses a simple selected-index setup.
    if(pauseSelectedIndex == 0)
    {
        paused = false;
    }
    else
    {
        GameData::createInstance()->setShouldQuit(true);
    }
}
