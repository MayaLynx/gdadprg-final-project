#include "GameResource.h"

GameResource* GameResource::myInstance = nullptr;

GameResource::GameResource()
{
    // This loads the shared assets once so the other classes can just reuse them.
    atlas = nullptr;

    // This loads the main shared assets here.
    // It saves the other classes from loading the same texture, font, or sound again.
    const bool textureLoaded = texture.loadFromFile("Assets/platformer_assets.png");
    const bool fontLoaded = font.openFromFile("Assets/Silver.ttf");

    // The atlas file tells the game where each sprite is inside the packed texture.
    if(textureLoaded && fontLoaded)
    {
        atlas = createDictionary("Assets/platformer_atlas.atlas");
    }

    // The BGM and jump SFX get loaded here too.
    const bool bgmLoaded = bgmBuffer.loadFromFile("Assets/bgm.wav");
    const bool jumpLoaded = jumpBuffer.loadFromFile("Assets/jump.wav");
    (void)bgmLoaded;
    (void)jumpLoaded;
}

GameResource::~GameResource()
{
    delete atlas;
}

GameResource* GameResource::createInstance()
{
    // This creates the shared resource manager the first time it is needed.
    if(myInstance == nullptr)
    {
        myInstance = new GameResource();
    }

    return myInstance;
}

std::unordered_map<std::string, sf::IntRect>* GameResource::getAtlas()
{
    return atlas;
}

sf::Texture* GameResource::getTexture()
{
    return &texture;
}

sf::Font* GameResource::getFont()
{
    return &font;
}

sf::SoundBuffer* GameResource::getBgmBuffer()
{
    return &bgmBuffer;
}

sf::SoundBuffer* GameResource::getJumpBuffer()
{
    return &jumpBuffer;
}
