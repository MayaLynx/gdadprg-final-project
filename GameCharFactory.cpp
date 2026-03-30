#include "GameCharFactory.h"
#include "MoveComp.h"
#include "JumpComp.h"
#include "GravityComp.h"

ModularGameObject* GameCharFactory::makePlayer(std::string name, float width, float height)
{
    ModularGameObject* player = new ModularGameObject(name, "idle/player-idle-1", width, height);

    player->attachComponent(new MoveComp());

  
    // Added the jump and gravity components to the player.
    player->attachComponent(new JumpComp(500.f));
    player->attachComponent(new GravityComp(1200.f, 700.f));

    player->setMoveSpeed(2.0f);
    player->setPosition(3, 3);

 
    // Player starts ungrounded until collision detects a floor/platform.
    player->setGrounded(false);

    return player;
}

GameObject* GameCharFactory::makeBlock(std::string name, int xPos, int yPos, float width, float height)
{
    GameObject* block = new GameObject(name, "block", width, height);
    block->setPosition(xPos, yPos);

    return block;
}