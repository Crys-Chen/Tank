

#include "MenuScreen.h"



using namespace sfGame;
extern AssetManager manager;
// extern std::shared_ptr<Screen> Game::Screen;


// Grades grades;

bool Button::inButton(sf::Vector2i pos)
{
    return (pos.x > left) && (pos.x < right) && (pos.y > top) && (pos.y < bottom);
}

MenuScreen::MenuScreen():play(363,560,680,795), exit(567,914,680,795),instruction(363,914,814,909)
{
    backGround.setTexture(AssetManager::getTexture("./pictures/begin.png"));
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if(event.type==sf::Event::Closed) window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			auto mousePos=sf::Mouse::getPosition(window); //根据sfml官网，获得当前鼠标位置
            if(play.inButton(mousePos))
            {
                if(Game::gameScreen != NULL)
                    delete Game::gameScreen;
                Game::gameScreen = new GameScreen();
                Game::gameScreen->initial();
                Game::screen = Game::gameScreen;
                
            }
            else if(exit.inButton(mousePos))
            {
                window.close();
            }
            else if(instruction.inButton(mousePos))
            {
                inst = true;
            }
            
		}

	}
}

void MenuScreen::update(sf::Time delta)
{
}

void MenuScreen::render(sf::RenderWindow& window, sf::View &view)
{
	window.draw(backGround);
}

