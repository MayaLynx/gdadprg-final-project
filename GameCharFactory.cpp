#include "GameCharFactory.h"
#include "MoveComp.h"
#include "JumpComp.h"
#include "GravityComp.h"

ModularGameObject* GameCharFactory::makePlayer(std::string name, float width, float height)
{
    ModularGameObject* player = new ModularGameObject(name, "idle/player-idle-1", width, height);

    player->attachComponent(new MoveComp());

  
    // Added the jump and gravity components to the player.
    player->attachComponent(new JumpComp(600.f));
    player->attachComponent(new GravityComp(1200.f, 700.f));

    player->setMoveSpeed(2.0f);
    player->setPosition(3, 8);

 
    // Player starts ungrounded until collision detects a floor/platform.
    player->setGrounded(false);

    return player;
}

ModularGameObject* GameCharFactory::makeEnemy(std::string name, int xPos, int yPos, float width, float height)
{
    ModularGameObject* enemy = new ModularGameObject(name, name + "-1", width, height);

    enemy->attachComponent(new JumpComp(500.f));
    enemy->attachComponent(new GravityComp(1200.f, 700.f));

    enemy->setMoveSpeed(2.0f);
    enemy->setMoveDirection(1);
    enemy->setPosition(xPos, yPos);
    enemy->setGrounded(false);

    return enemy;
}

GameObject* GameCharFactory::makeBlock(std::string name, int xPos, int yPos, float width, float height)
{
    GameObject* block = new GameObject(name, "block", width, height);
    block->setPosition(xPos, yPos);

    return block;
}