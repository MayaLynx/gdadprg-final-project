#include "AtlasParserM.h"
#include "GameResource.h"

#include "Scene.h"
#include "SceneManager.h"
#include "MarioBrosEngine.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    sf::Music bgm("Assets\\Pixel Time.mp3");
    bgm.setVolume(10.f);
    bgm.setLooping(true);
    bgm.play();

    MarioBrosEngine game;
    game.run("Test", game.getWindowWidth(), game.getWindowHeight());

    return 0;
}