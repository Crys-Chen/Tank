#include "GameOverScreen.h"

using namespace sfGame;

GameOverScreen::GameOverScreen()
{
	font=AssetManager::getFont("Fonts/game.ttf");
	text.setFont(font);
    // text.setString("Game over ! ! ! " );
    std::string winner = Battlefield::getWinner() == Side::Blue? "Blue" : "Red";
    
	text.setString("Game over ! ! ! \n\n Winner: " +
         winner +
		"\n\nPress [SPACE] to retry"+
		"\n\nPress [ESC] to quit");

	text.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text.setPosition(Parameter::windowWidth / 2, Parameter::windowHeight / 2);
    std::cout<<winner<<std::endl;
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if(event.type==sf::Event::Closed) window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Game::screen = std::make_shared<MenuScreen>();
		}
	    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
	}
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window, sf::View &view)
{
	// if(break_record_==true) window.draw(break_record_text);
	window.draw(text);
}
