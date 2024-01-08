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
#include "Game.h"
#include "GameOverScreen.h"

namespace sfGame
{

class GameScreen : public Screen
{
    public:
        GameScreen();
        ~GameScreen();

        void initial();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window, sf::View &view) override;

    private:
        BackGround backGround;
        Player *player;
        // std::shared_ptr<Battlefield> battlefield;
        Battlefield *battlefield;
        std::future<void> gen[2];

       
	
};
}

#endif