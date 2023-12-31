#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <memory>
#include <cstdlib>

#include "Screen.h"
#include "MenuScreen.h"
#include "AssetManager.h"
#include "Battlefield.h"

namespace sfGame
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();
	sf::Vector2i window_pos(); 

	static const int windowWidth = 1280;
	static const int windowHeight = 960;

    // static const int gameWidth = ;
    // static const int gameHeight = ;

	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window;
	sf::Music bgMusic;
    sf::View view;

	static const sf::Time TimePerFrame;
};
}


#endif