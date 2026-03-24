#pragma once

#include "AtlasParserM.h"
#include <SFML/Graphics.hpp>

class GameResource{
	public:
		static GameResource* createInstance();
		std::unordered_map<std::string,sf::IntRect>* getAtlas();
		sf::Texture* getTexture();
		sf::Font* getFont();
		~GameResource();
	private:
		static GameResource* myInstance;
		std::unordered_map<std::string,sf::IntRect>* atlas;
		sf::Texture texture;
		sf::Font font;
		GameResource();
};
