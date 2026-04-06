#include "GameData.h"

GameData* GameData::myInstance = nullptr;

GameData* GameData::createInstance()
{
    // This stores the run data so different scenes can still share score, lives, stage, and time.
    if(myInstance == nullptr)
    {
        myInstance = new GameData();
    }

    return myInstance;
}

GameData::GameData()
{
    resetRun();
}

void GameData::resetRun()
{
    // This resets the whole run.
    // It helps when the player restarts after game over or after clearing all levels.
    stage = 1;
    lives = 3;
    score = 0;
    elapsedTime = 0.f;
    resultMessage.clear();
    shouldQuit = false;
}

int GameData::getStage() const
{
    return stage;
}

void GameData::setStage(int val)
{
    stage = val;
}

int GameData::getLives() const
{
    return lives;
}

void GameData::setLives(int val)
{
    lives = val;
}

int GameData::getScore() const
{
    return score;
}

void GameData::setScore(int val)
{
    score = val;
}

void GameData::addScore(int amount)
{
    score += amount;
}

float GameData::getElapsedTime() const
{
    return elapsedTime;
}

void GameData::setElapsedTime(float seconds)
{
    elapsedTime = seconds;
}

void GameData::addElapsedTime(float seconds)
{
    elapsedTime += seconds;
}

std::string GameData::getResultMessage() const
{
    return resultMessage;
}

void GameData::setResultMessage(const std::string& message)
{
    resultMessage = message;
}

bool GameData::getShouldQuit() const
{
    return shouldQuit;
}

void GameData::setShouldQuit(bool value)
{
    shouldQuit = value;
}
