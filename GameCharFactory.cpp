#include "GameCharFactory.h"

ModularGameObject* GameCharFactory::makePlayer(std::string name, float width, float height)
{
    ModularGameObject* player = new ModularGameObject(name, "idle/player-idle-1", width, height);
    player->attachComponent(new MoveComp());
    player->setMoveSpeed(2.0);
    player->setPosition(3, 3);

    return player;
}

GameObject* GameCharFactory::makeBlock(std::string name, int xPos, int yPos, float width, float height)
{
    GameObject* block = new GameObject(name, "block", width, height);
    block->setPosition(xPos, yPos);

    return block;
}