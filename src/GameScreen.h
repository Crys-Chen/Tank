#ifndef GAMESCREEN
#define GAMESCREEN

#include <SFML/Graphics.hpp>
#include <vector>


#include "Screen.h"
#include "AssetManager.h"
#include "BackGround.h"
#include "Battlefield.h"
#include "Player.h"
#include "Tower.h"
#include "Soldier.h"

namespace sfGame
{

class GameScreen : public Screen
{
    public:
        GameScreen();
        ~GameScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window, sf::View &view) override;

        void generateSoldiers(sf::Time delta);

        static sf::Clock clock;
        

    private:
        BackGround backGround;
        // Units units;
        Nexus *blueNexus, *redNexus;
        Tower *blueTowers, *redTowers;
        Player *player;
        // Distance *distance;
        // sf::Sprite blueNexusSprite, redNexusSprite;
        sf::Sprite blueTowerSprite[5], redTowerSprite[5];
        sf::Sprite blueSoldierSprite[3], redSoldierSprite[3];
        sf::Sprite playerSprite;
        sf::Sprite blueObstacle[4], redObstacle[4];
        // sf::Time generateInterval;
       
	
};
}

#endif