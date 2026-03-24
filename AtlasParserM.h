#pragma once
#include <fstream>
//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
//#include <cmath>
#include <string>
#include <cstring>
//#include <climits>
//#include <numeric>
//#include <iomanip>
//#include <functional>
#include <sstream>

#include <cstdlib>
#include <unordered_map>
#include <SFML/Graphics.hpp>

bool comparePrefix(std::string word, std::string prefix);
bool containsChar(std::string word, char character);
std::unordered_map<std::string,sf::IntRect>* createDictionary(std::string atlasFile);

