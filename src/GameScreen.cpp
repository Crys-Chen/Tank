

#include "GameScreen.h"
// #include "Game.h"

using namespace sfGame;
extern AssetManager manager;
extern Battlefield battlefield;

sf::Clock GameScreen::clock;

const sf::Vector2f blueTowersPos[5] = {sf::Vector2f(640,90), sf::Vector2f(415,688), sf::Vector2f(880,688), sf::Vector2f(370,1197), sf::Vector2f(1028,1197)};
const sf::Vector2f redTowersPos[5] = {sf::Vector2f(640,2810), sf::Vector2f(415,2210), sf::Vector2f(880,2210), sf::Vector2f(275,1710), sf::Vector2f(933,1710)};

GameScreen::GameScreen(): 
    backGround()
{
    for(int i = 0; i < 5; i++)
    {
        blueTowerSprite[i].setTexture(AssetManager::getTexture("./pictures/tower1.png"));
        blueTowerSprite[i].setOrigin(sf::Vector2f(46.5,48));
        blueTowerSprite[i].setPosition(blueTowersPos[i]);
        if(i == 0)
        {
            blueNexus = new Nexus(Side::Blue, blueTowerSprite[i], 1, 1, 1);
            Battlefield::registerUnit(blueNexus);
        }
        else
            Battlefield::registerUnit(new Tower(Side::Blue, blueTowerSprite[i], 1, 1, 1));

        redTowerSprite[i].setTexture(AssetManager::getTexture("./pictures/tower2.png"));
        redTowerSprite[i].setOrigin(sf::Vector2f(46.5,48));
        redTowerSprite[i].setPosition(redTowersPos[i]);
        if(i == 0)
        {
            redNexus = new Nexus(Side::Red, redTowerSprite[i], 1, 1, 1);
            Battlefield::registerUnit(redNexus);
        }
        else
            Battlefield::registerUnit(new Tower(Side::Red, redTowerSprite[i], 1, 1, 1));
    }

    // blueNexusSprite.setTexture(AssetManager::getTexture("./pictures/tower1.png"));
    // blueNexusSprite.setOrigin(sf::Vector2f(46.5,48));
    // blueNexusSprite.setPosition(sf::Vector2f(640,90));
    // blueNexus = new Nexus(Side::Blue, blueNexusSprite, 1, 1, 1);
    // Battlefield::registerUnit(blueNexus);

    // blueTowerSprite[0].setTexture(AssetManager::getTexture("./pictures/tower1.png"));
    // blueTowerSprite[0].setOrigin(sf::Vector2f(46.5,48));
    // blueTowerSprite[0].setPosition(sf::Vector2f(415,688));
    // blueTowers = new Tower(Side::Blue, blueTowerSprite[0], 1, 1, 1);
    // Battlefield::registerUnit(blueTowers);

    // blueTowerSprite[1] = blueTowerSprite[0];
    // blueTowerSprite[1].setPosition(sf::Vector2f(880,688));
    // blueTowers = new Tower(Side::Blue, blueTowerSprite[1], 1, 1, 1);
    // Battlefield::registerUnit(blueTowers);

    // blueTowerSprite[2] = blueTowerSprite[0];
    // blueTowerSprite[2].setPosition(sf::Vector2f(370,1197));
    // blueTowers = new Tower(Side::Blue, blueTowerSprite[2], 1, 1, 1);
    // Battlefield::registerUnit(blueTowers);

    // blueTowerSprite[3] = blueTowerSprite[0];
    // blueTowerSprite[3].setPosition(sf::Vector2f(1028,1197));
    // blueTowers = new Tower(Side::Blue, blueTowerSprite[3], 1, 1, 1);
    // Battlefield::registerUnit(blueTowers);

    playerSprite.setTexture(AssetManager::getTexture("./pictures/hero.png"));
    playerSprite.setOrigin(sf::Vector2f(18,18));
    playerSprite.setPosition(sf::Vector2f(800,85));
    playerSprite.setScale(2,2);
    player = new Player(Side::Blue, playerSprite, 1, 1, 1);
    Battlefield::registerUnit(player);


    blueNexus->generateSoldiers();
    redNexus->generateSoldiers();




    // redNexus = new Nexus(Side::Red, blueTowerSprite, 1, 1, 1);
    // Battlefield::registerUnit(redNexus);
    // player = new Player(Side::Blue, playerSprite, 1, 1, 1);
    // for(int i = 0; i < 5; i++)
    // {
    //     blueTowers = new Tower(Side::Blue, blueTowerSprite, 1, 1, 1);
    //     Battlefield::registerUnit(blueTowers);
    //     redTowers = new Tower(Side::Red, blueTowerSprite, 1, 1, 1);
    //     Battlefield::registerUnit(redTowers);
    // }
    // //generateSoldiers(sf::seconds(1));
    // distance = new Distance(units);
    // std::cout<<"created gameScreen!"<<std::endl;

}

GameScreen::~GameScreen()
{
    
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	player->handleInput(window);
    
	// sf::Event event;
	// while(window.pollEvent(event))
	// {
	// 	if(event.type==sf::Event::Closed) window.close();
	// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	// 		window.close();
    //     else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	// 	{
	// 		auto mousePos=sf::Mouse::getPosition(window); //根据sfml官网，获得当前鼠标位置
    //         std::cout << mousePos.x << "," << mousePos.y << std::endl;
    //     //     if(play.inButton(mousePos))
    //     //     {
    //     //         std::cout<<"play!"<<std::endl;
    //     //         Game::Screen = std::make_shared<GameScreen>();
    //     //     }
    //     //     else if(exit.inButton(mousePos))
    //     //     {
    //     //         // std::cout<<"play!"<<std::endl;
    //     //         window.close();
    //     //     }
    //     //     else if(instruction.inButton(mousePos))
    //     //     {
    //     //         // Game::Screen = std::make_shared<MenuScreen_2>();
    //     //         std::cout<<"instruction!"<<std::endl;
    //     //         inst = true;
    //     //     }
            
	// 	}
	// }
}

void GameScreen::update(sf::Time delta) //未完成
{
	//generateSoldiers(delta);

    Battlefield::update(delta);


}

void GameScreen::render(sf::RenderWindow& window, sf::View &view)
{
	backGround.draw(window);
    // while(view.getCenter().y < 960)

    if(player->getPos().y < 480 || player->getPos().y > 2400)
        view.setCenter(sf::Vector2f(640, view.getCenter().y));
    else 
	    view.setCenter(sf::Vector2f(640, player->getPos().y));

	for (auto unit : Battlefield::getUnits())
		unit->render(window);
}

// void GameScreen::generateSoldiers(sf::Time delta)
// {
//     Battlefield::generateSoldiers(delta, blueNexus, redNexus);
        
//     // Soldier *blueSoldiers = NULL;
//     // if(blueNexus->isDead() == false)
//     // {
//     //     blueNexus->generateSoldiers(blueSoldiers, delta);
//     //     if(blueSoldiers)
//     //     {
//     //         for(int i = 0; i < 9; i++)
//     //         {
//     //             registerUnit(blueSoldiers+i);
//     //         }
//     //     }
//     // }

//     // Soldier *redSoldiers = NULL;
//     // if(redNexus->isDead() == false)
//     // {
//     //     redNexus->generateSoldiers(redSoldiers, delta);
//     //     if(redSoldiers)
//     //     {
//     //         for(int i = 0; i < 9; i++)
//     //         {
//     //             registerUnit(redSoldiers+i);
//     //         }
//     //     }
//     // }
    
// }

