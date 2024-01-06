#include "Game.h"

using namespace sfGame;

AssetManager manager;

ThreadPool threadPool(30);

const sf::Time Game::TimePerFrame = Parameter::timePerFrame;

// std::shared_ptr<Screen> Game::screen = std::make_shared<GameScreen>();
// Screen* Game::screen = new GameScreen();
Screen* Game::screen = new MenuScreen();


Game::Game(): window(sf::VideoMode(Parameter::windowWidth, Parameter::windowHeight), "sfTank"),
view(sf::FloatRect(0.f, 0.f, Parameter::windowWidth, Parameter::windowHeight))
{
    threadPool.init();
	// bgMusic.openFromFile("Music/bg_music.wav");
	// bgMusic.setLoop(true);
	// bgMusic.play();
    
}

Game::~Game()
{
    threadPool.shutdown();
    delete screen;
}

sf::Vector2i Game::windowPos()
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
	Game::screen->handleInput(window);
}

void Game::update()
{
    sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			Game::screen->update(TimePerFrame);
		}
		
	}
	
}

void gameUpdate(Game *game)
{
    game->update();
}

void Game::render()
{
	window.clear();
	Game::screen->render(window,view);
    window.setView(view);
	window.display();
}

void Game::run()
{
    threadPool.submit(gameUpdate, this);
    while(window.isOpen())
    {
        handleInput();
        render();
    }
    delete Game::screen;

	// }

	// sf::Clock clock;
	// sf::Time timeSinceLastUpdate = sf::Time::Zero;
	// std::srand(std::time(NULL));

	// while (window.isOpen())
	// {
	// 	sf::Time delta = clock.restart();
	// 	timeSinceLastUpdate += delta;

	// 	while (timeSinceLastUpdate > Game::TimePerFrame)
	// 	{
	// 		timeSinceLastUpdate -= TimePerFrame;
	// 		handleInput();
	// 		update(TimePerFrame);
	// 	}

	// 	render();
	// }
}