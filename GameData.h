#pragma once

#include <string>

class GameData
{
public:
    static GameData* createInstance();

    void resetRun();

    int getStage() const;
    void setStage(int val);

    int getLives() const;
    void setLives(int val);

    int getScore() const;
    void setScore(int val);
    void addScore(int amount);

    float getElapsedTime() const;
    void setElapsedTime(float seconds);
    void addElapsedTime(float seconds);

    std::string getResultMessage() const;
    void setResultMessage(const std::string& message);

    bool getShouldQuit() const;
    void setShouldQuit(bool value);

private:
    static GameData* myInstance;

    int stage;
    int lives;
    int score;
    float elapsedTime;
    std::string resultMessage;
    bool shouldQuit;

    GameData();
};
