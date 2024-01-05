

#include "GameScreen.h"
// #include "Game.h"

using namespace sfGame;
extern AssetManager manager;
// extern Battlefield battlefield;
extern ThreadPool threadPool;

sf::Clock GameScreen::clock;

const std::vector<sf::Vector2f> blueTowersPos = Parameter::blueTowersPos;
const std::vector<sf::Vector2f> redTowersPos = Parameter::redTowersPos;


GameScreen::GameScreen(): 
    backGround()
{
    Battlefield::instance = new Battlefield();
    assert(player == NULL);
    Nexus *blueNexus = NULL, *redNexus = NULL;
    sf::Sprite blueTowerSprite[5], redTowerSprite[5];
    sf::Sprite blueSoldierSprite[3], redSoldierSprite[3];
    sf::Sprite playerSprite;
    for(int i = 0; i < 5; i++)
    {
        blueTowerSprite[i].setTexture(AssetManager::getTexture("./pictures/tower1.png"));
        blueTowerSprite[i].setOrigin(sf::Vector2f(46.5,48));
        blueTowerSprite[i].setPosition(blueTowersPos[i]);
        if(i == 0)
        {
            blueNexus = new Nexus(Side::Blue, blueTowerSprite[i], Parameter::towerHP, Parameter::towerATK, Parameter::towerAttackRange, Parameter::towerAttackInterval, Parameter::towerFOV);
            Battlefield::registerUnit(blueNexus);
        }
        else
            Battlefield::registerUnit(new Tower(Side::Blue, blueTowerSprite[i], Parameter::towerHP, Parameter::towerATK, Parameter::towerAttackRange, Parameter::towerAttackInterval, Parameter::towerFOV));

        redTowerSprite[i].setTexture(AssetManager::getTexture("./pictures/tower2.png"));
        redTowerSprite[i].setOrigin(sf::Vector2f(46.5,48));
        redTowerSprite[i].setPosition(redTowersPos[i]);
        if(i == 0)
        {
            redNexus = new Nexus(Side::Red, redTowerSprite[i], Parameter::towerHP, Parameter::towerATK, Parameter::towerAttackRange, Parameter::towerAttackInterval, Parameter::towerFOV);
            Battlefield::registerUnit(redNexus);
        }
        else
            Battlefield::registerUnit(new Tower(Side::Red, redTowerSprite[i], Parameter::towerHP, Parameter::towerATK, Parameter::towerAttackRange, Parameter::towerAttackInterval, Parameter::towerFOV));
    }


    playerSprite.setTexture(AssetManager::getTexture("./pictures/hero.png"));
    playerSprite.setOrigin(sf::Vector2f(18,18));
    playerSprite.setPosition(sf::Vector2f(800,85));
    playerSprite.setScale(2,2);
    player = new Player(Side::Blue, playerSprite, Parameter::playerHP, Parameter::playerATK, Parameter::playerAttackRange, Parameter::playerAttackInterval, 1);
    Battlefield::registerUnit(player);

    threadPool.submit(generateSoldiers, blueNexus);
    threadPool.submit(generateSoldiers, redNexus);




    // redNexus = new Nexus(Side::Red, blueTowerSprite, 1, 1, 1);
    // Battlefield::registerUnit(redNexus);
    // player = new Player(Side::Blue, playerSprite, 1, 1, 1);
    // for(int i = 0; i < 5; i++)
    // {
    //     blueTower = new Tower(Side::Blue, blueTowerSprite, 1, 1, 1);
    //     Battlefield::registerUnit(blueTower);
    //     redTower = new Tower(Side::Red, blueTowerSprite, 1, 1, 1);
    //     Battlefield::registerUnit(redTower);
    // }
    // //generateSoldiers(sf::seconds(1));
    // distance = new Distance(units);
    // std::cout<<"created gameScreen!"<<std::endl;

}

// GameScreen::~GameScreen()
// {
    
// }

void GameScreen::generateSoldiers(Nexus *nexus)
{
    // std::cout<<"here!"<<std::endl;
    nexus->generateSoldiers();
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
    {
        if(unit->isDead()) continue;
        unit->render(window);
    }
		
    for (auto shell: Battlefield::getShells())
        shell->render(window);
}



