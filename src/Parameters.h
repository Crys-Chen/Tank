#ifndef PARAMETER
#define PARAMETER

#include <vector>
#include <SFML/Graphics.hpp>

namespace Parameter{

const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
const int windowWidth = 1280;
const int windowHeight = 960;
const int mapWidth = 1280;
const int mapHeight = 960 * 3;
const int middle = windowWidth / 2;

const float genSoldierInterval = 5.0;

const float soldierFOV = 100;
const float towerFOV = 300;

const std::vector<sf::Vector2f> blueTowersPos = {sf::Vector2f(middle,90), sf::Vector2f(415,688), sf::Vector2f(880,688), sf::Vector2f(370,1197), sf::Vector2f(1028,1197)};
const std::vector<sf::Vector2f> redTowersPos = {sf::Vector2f(middle,2810), sf::Vector2f(415,2210), sf::Vector2f(880,2210), sf::Vector2f(275,1710), sf::Vector2f(933,1710)};

typedef std::vector<sf::Vector2f> Route;
const Route blueMidRoute = {sf::Vector2f(middle, 197), sf::Vector2f(middle, 738), sf::Vector2f(middle, 1440), sf::Vector2f(middle, 1950), sf::Vector2f(middle, 2683)};
const Route blueLeftRoute = {sf::Vector2f(548, 84), sf::Vector2f(105, 289), sf::Vector2f(105, 1440), sf::Vector2f(105, 2591), sf::Vector2f(548, 2796)};
const Route blueRightRoute = {sf::Vector2f(755, 84), sf::Vector2f(1175, 289), sf::Vector2f(1175, 1440), sf::Vector2f(1175, 2591), sf::Vector2f(755, 2796)};

const Route redMidRoute = {blueMidRoute[4], blueMidRoute[3], blueMidRoute[2], blueMidRoute[1], blueMidRoute[0]};
const Route redLeftRoute = {blueLeftRoute[4], blueLeftRoute[3], blueLeftRoute[2], blueLeftRoute[1], blueLeftRoute[0]};
const Route redRightRoute = {blueRightRoute[4], blueRightRoute[3], blueRightRoute[2], blueRightRoute[1], blueRightRoute[0]};

const float soldierGap = 60;
}

#endif