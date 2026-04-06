#include "GameCharFactory.h"
#include "MoveComp.h"
#include "JumpComp.h"
#include "GravityComp.h"

ModularGameObject* GameCharFactory::makePlayer(std::string name, float width, float height)
{
    // This builds the player in one place so the scenes do not keep repeating the same setup.
    ModularGameObject* player = new ModularGameObject(name, "idle/player-idle-1", width, height);

    player->attachComponent(new MoveComp());
    player->attachComponent(new JumpComp(820.f));
    player->attachComponent(new GravityComp(1700.f, 950.f));

    // Move speed is time-based now, so this value is in pixels per second.
    player->setMoveSpeed(240.f);
    player->setGrounded(false);

    return player;
}

GameObject* GameCharFactory::makeBlock(std::string name, int xPos, int yPos, float width, float height)
{
    GameObject* block = new GameObject(name, "block-big", width, height);
    block->setPosition(xPos, yPos);
    return block;
}

GameObject* GameCharFactory::makeGoal(std::string name, int xPos, int yPos, float width, float height)
{
    GameObject* goal = new GameObject(name, "door-opened", width, height);
    goal->setPosition(xPos, yPos);
    return goal;
}

GameObject* GameCharFactory::makeCollectible(std::string name, int xPos, int yPos, float width, float height)
{
    GameObject* collectible = new GameObject(name, "shrooms", width, height);
    collectible->setPosition(xPos, yPos);
    return collectible;
}
