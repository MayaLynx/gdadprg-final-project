#include "GameScene.h"

GameScene::GameScene() : Scene("GameScene")
{
    if(jumpSFX_buffer.loadFromFile("Assets\\jump.wav"))
    {
        jumpSFX = new sf::Sound(jumpSFX_buffer);
        jumpSFX->setVolume(30.f);
    }

}

void GameScene::onLoad()
{
    GameData* gameData = GameData::createInstance();
    std::vector<GameObject*> snapshot = gameData->getSnapshot();

    // Enzo changes
    // Resets the solid block list whenever the scene loads
    solidBlocks.clear();
    
    // Sets up the camera for scrolling.
    camera.setSize({500.f, 500.f});
    camera.setCenter({250.f, 250.f});
    stageWidth = 2640.f;

    if(snapshot.empty())
    {
        stage = 1;
        lives = 3;

        GameObject* game_bg = new Background("game_bg", "background", stageWidth, 500.f);
        addObject(game_bg);

        ModularGameObject* player = GameCharFactory::makePlayer("player", 33, 32);
        addObject(player);

        ModularGameObject* enemy = GameCharFactory::makeEnemy("opossum", 25, 4, 36, 28);
        addObject(enemy);
       
        // Builsd a simple block-based stage for testing collision and jump.
        buildSimpleStage();

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

        
        // Rebuild the list of solid stage blocks after loading from snapshot.
        for(GameObject* obj : getAllObjects())
        {
            if(obj->getName() != "player")
            {
                solidBlocks.push_back(obj);
            }
        }
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
    ModularGameObject* enemy = (ModularGameObject*)findObject("opossum");

    if(player == nullptr)
        return;

    player->update(deltaTime);

    
    // After components move the sprite, fix block overlaps and then updates camera.
    handleCollisions(player);
    updateCamera(player);

    // Test enemy
    if(enemy == nullptr)
        return;
    enemy->update(deltaTime);
    handleCollisions(enemy);
}

void GameScene::draw(sf::RenderWindow* window)
{
    
    // Draws the stage through the camera view.
    window->setView(camera);
    Scene::draw(window);
    window->setView(window->getDefaultView());
}

void GameScene::keyPressTrigger(sf::Keyboard::Scan keyCode)
{
    ModularGameObject* player = (ModularGameObject*)findObject("player");

    if(player == nullptr)
        return;

    if(keyCode == sf::Keyboard::Scan::Left)
    {
        player->setMoveDirection(LEFT);
    }
    else if(keyCode == sf::Keyboard::Scan::Right)
    {
        player->setMoveDirection(RIGHT);
    }
    else if(keyCode == sf::Keyboard::Scan::Space ||
            keyCode == sf::Keyboard::Scan::Z ||
            keyCode == sf::Keyboard::Scan::Up)
    {
        // Only play jump SFX when the player is actually able to jump.
        if(player->isGrounded())
        {
            jumpSFX->play();
        }
        // Request a jump instead of directly changing position here.
        player->requestJump();
    }

    // Ability to run when held down
    if(keyCode == sf::Keyboard::Scan::X)
    {
        player->setMoveSpeed(5.0);
    }
}

void GameScene::keyReleaseTrigger(sf::Keyboard::Scan keyCode)
{
    ModularGameObject* player = (ModularGameObject*)findObject("player");

    if(player == nullptr)
        return;

    if(keyCode == sf::Keyboard::Scan::Left ||
       keyCode == sf::Keyboard::Scan::Right)
    {
        player->setMoveDirection(STOPPED);
    }

    // Player speed returns to normal when released
    if(keyCode == sf::Keyboard::Scan::X)
    {
        player->setMoveSpeed(3.0);
    }
}

bool GameScene::rectanglesOverlap(const sf::FloatRect& a, const sf::FloatRect& b)
{
    return a.position.x < b.position.x + b.size.x &&
           a.position.x + a.size.x > b.position.x &&
           a.position.y < b.position.y + b.size.y &&
           a.position.y + a.size.y > b.position.y;
}

void GameScene::buildSimpleStage()
{
    // FOR TESTING
    // Build a basic floor and a few platforms so jump/gravity/collision can be tested.
    for(int i = 0; i < 40; i++)
    {
        GameObject* block = GameCharFactory::makeBlock("floor" + std::to_string(i), i, 10, 35, 35);
        addObject(block);
        solidBlocks.push_back(block);
    }

    GameObject* block1 = GameCharFactory::makeBlock("plat1", 8, 9, 35, 35);
    GameObject* block2 = GameCharFactory::makeBlock("plat2", 9, 9, 35, 35);
    GameObject* block3 = GameCharFactory::makeBlock("plat3", 14, 7, 35, 35);
    GameObject* block4 = GameCharFactory::makeBlock("plat4", 15, 7, 35, 35);
    GameObject* block5 = GameCharFactory::makeBlock("plat5", 16, 7, 35, 35);

    addObject(block1);
    addObject(block2);
    addObject(block3);
    addObject(block4);
    addObject(block5);

    solidBlocks.push_back(block1);
    solidBlocks.push_back(block2);
    solidBlocks.push_back(block3);
    solidBlocks.push_back(block4);
    solidBlocks.push_back(block5);
}

void GameScene::handleCollisions(ModularGameObject* player)
{
    sf::FloatRect playerBounds = player->getBounds();

    // Enzo changes
    // Assume the player is not on the ground first.
    // If we detect a landing on a block, grounded becomes true.
    player->setGrounded(false);

    for(GameObject* block : solidBlocks)
    {
        sf::FloatRect blockBounds = block->getBounds();

        if(rectanglesOverlap(playerBounds, blockBounds))
        {
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

            
            // ResolveS using the smaller overlap axis.
            // Horizontal overlap means wall correction.
            // Vertical overlap means floor/ceiling correction.
            if(overlapX < overlapY)
            {
                if(player->getMoveDirection() == RIGHT)
                {
                    player->getSprite()->move({-overlapX, 0.f});
                }
                else if(player->getMoveDirection() == LEFT)
                {
                    player->getSprite()->move({overlapX, 0.f});
                }
            }
            else
            {
                if(player->getVerticalVelocity() > 0)
                {
                    player->getSprite()->move({0.f, -overlapY});
                    player->setVerticalVelocity(0.f);
                    player->setGrounded(true);
                }
                else if(player->getVerticalVelocity() < 0)
                {
                    player->getSprite()->move({0.f, overlapY});
                    player->setVerticalVelocity(0.f);
                }
            }

            playerBounds = player->getBounds();
        }
    }
}

void GameScene::updateCamera(ModularGameObject* player)
{
    float halfWidth = camera.getSize().x / 2.f;
    float camX = player->getWorldPosition().x;

    
    // Clamps camera so it follows the player but does not move past the level edges.
    if(camX < halfWidth)
        camX = halfWidth;

    if(camX > stageWidth - halfWidth)
        camX = stageWidth - halfWidth;

    camera.setCenter({camX, 250.f});
}