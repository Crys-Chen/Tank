#ifndef GAMESCREEN
#define GAMESCREEN

#include <SFML/Graphics.hpp>
#include <vector>

#include "ThreadPool.h"
#include "Parameters.h"
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
        ~GameScreen() = default;

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window, sf::View &view) override;

    private:
        BackGround backGround;
        static Player *player;

       
	
};
}

#endif