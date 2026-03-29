#include "GameResource.h"

GameResource* GameResource::myInstance = nullptr;

GameResource::GameResource(){
    if(texture.loadFromFile("Assets\\platformer_assets.png")
            && font.openFromFile("Assets\\Silver.ttf") ){
        atlas = createDictionary("Assets\\platformer_atlas.atlas");
	}
}

GameResource::~GameResource(){
    delete atlas;
}

GameResource* GameResource::createInstance(){
    if(myInstance == nullptr)
        myInstance = new GameResource();
    return myInstance;
}

std::unordered_map<std::string,sf::IntRect>* GameResource::getAtlas(){
    return atlas;
}
sf::Texture* GameResource::getTexture(){
    return &texture;
}
sf::Font* GameResource::getFont(){
    return &font;
}
