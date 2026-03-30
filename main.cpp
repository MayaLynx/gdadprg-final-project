#include "AtlasParserM.h"
#include "GameResource.h"

#include "Scene.h"
#include "SceneManager.h"
#include "MarioBrosEngine.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    MarioBrosEngine game;
    game.run("Test", game.getWindowWidth(), game.getWindowHeight());

    return 0;
}