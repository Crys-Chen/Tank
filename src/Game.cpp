#include "Game.h"

using namespace sfGame;

AssetManager manager;

ThreadPool threadPool(30);

const sf::Time Game::TimePerFrame = Parameter::timePerFrame;

std::shared_ptr<Screen> Game::screen = std::make_shared<MenuScreen>();
// Screen* Game::screen = new GameScreen();
// Screen* Game::screen = new MenuScreen();


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
    // delete screen;
}

sf::Vector2i Game::windowPos()
{
    return window.getPosition();
}


void Game::handleInput()
{
	//为支持多样的输入处理，必须代理给具体screen的handleinput实现
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


void Game::render()
{
	window.clear();
	Game::screen->render(window,view);
    window.setView(view);
	window.display();
}

void Game::run()
{
    auto future = threadPool.submit([=]{update();});
    while(window.isOpen())
    {
        std::this_thread::sleep_for(std::chrono::seconds(int(Game::TimePerFrame.asSeconds())));
        handleInput();
        render();
    }
    future.get();
    std::cout<<"close"<<std::endl;
    // delete Game::screen;
    exit(0);
}