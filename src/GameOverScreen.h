#ifndef GAMEOVERSCREEN
#define GAMEOVERSCREEN

#include "Game.h"
#include "Battlefield.h"
#include "Screen.h"
#include <string>


namespace sfGame
{

class GameOverScreen : public Screen
{
    public:
        GameOverScreen();
        ~GameOverScreen() = default;

        void initial();
        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window, sf::View &view) override;

    private:
        sf::Font font;
        sf::Text text;
       
	
};

}


#endif