#ifndef MENU_SCREEN
#define MENU_SCREEN

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <string>
#include "Game.h"
#include "Screen.h"
#include "GameScreen.h"
#include "AssetManager.h"
// #include "Game.h"

namespace sfGame
{

class Button 
{
    private:
        int left,right,top,bottom;

    public: 
        Button(int left, int right, int top, int bottom):
            left(left),right(right),top(top),bottom(bottom){}
        bool inButton(sf::Vector2i pos);
};

class MenuScreen : public Screen
{
    public:
        MenuScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window,sf::View& view) override;


    private:
        sf::Sprite backGround;
        bool inst;
        Button play;
        Button exit;
        Button instruction;
        

};
}

#endif