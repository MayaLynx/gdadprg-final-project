#pragma once

#include "AtlasParserM.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameResource
{
public:
    static GameResource* createInstance();

    std::unordered_map<std::string, sf::IntRect>* getAtlas();
    sf::Texture* getTexture();
    sf::Font* getFont();
    sf::SoundBuffer* getBgmBuffer();
    sf::SoundBuffer* getJumpBuffer();

    ~GameResource();

private:
    static GameResource* myInstance;

    std::unordered_map<std::string, sf::IntRect>* atlas;
    sf::Texture texture;
    sf::Font font;
    sf::SoundBuffer bgmBuffer;
    sf::SoundBuffer jumpBuffer;

    GameResource();
};
