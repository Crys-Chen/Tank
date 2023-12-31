#include "Game.h"

using namespace sfGame;

AssetManager manager;
Battlefield battlefield;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();


Game::Game(): window(sf::VideoMode(Game::windowWidth, Game::windowHeight), "sfTank"),
view(sf::FloatRect(0.f, 0.f, Game::windowWidth, Game::windowHeight))
{
	bgMusic.openFromFile("Music/bg_music.wav");
	bgMusic.setLoop(true);
	bgMusic.play();
}

sf::Vector2i Game::window_pos()
{
    return window.getPosition();
}


void Game::handleInput()
{
	// sf::Event event;

	// while (window.pollEvent(event))
	// {
	// 	if (event.type == sf::Event::Closed)
	// 		window.close();
	// }
	//为支持多样的输入处理，必须把event放到各个screen的handleinput中poll
	Game::Screen->handleInput(window);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window.clear();
	Game::Screen->render(window,view);
    window.setView(view);
	window.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	std::srand(std::time(NULL));

	while (window.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}