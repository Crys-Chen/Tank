

#include "GameScreen.h"
// #include "Game.h"

using namespace sfGame;
extern AssetManager manager;
// extern Battlefield battlefield;
extern ThreadPool threadPool;

Player* GameScreen::player = NULL;
// sf::Clock GameScreen::clock;

const std::vector<sf::Vector2f> blueTowersPos = Parameter::blueTowersPos;
const std::vector<sf::Vector2f> redTowersPos = Parameter::redTowersPos;

void generateSoldiers(Nexus *nexus)
{
    nexus->generateSoldiers();
}


GameScreen::GameScreen(): 
    backGround()
{
    new Battlefield();
    assert(player == NULL);
    std::cout<<"here!"<<std::endl;
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






}



void GameScreen::handleInput(sf::RenderWindow& window)
{
	player->handleInput(window);
}

void refresh(Player *player)
{
    player->refresh();
}

void GameScreen::update(sf::Time delta) 
{
    static bool playerRefresh = false;

    Battlefield::update(delta);
    if(player->isDead())
    {
        if(playerRefresh == false)
            threadPool.submit(refresh,player);
        playerRefresh = true;
    }
    else playerRefresh = false;
    
        
}

void GameScreen::render(sf::RenderWindow& window, sf::View &view)
{
	backGround.draw(window);
    // while(view.getCenter().y < 960)
    if(player->isDead())
        view.setCenter(sf::Vector2f(640,480));
    else
    {
        if(player->getPos().y < 480 || player->getPos().y > 2400)
            view.setCenter(sf::Vector2f(640, view.getCenter().y));
        else 
            view.setCenter(sf::Vector2f(640, player->getPos().y));
    }


	for (auto unit : Battlefield::getUnits())
    {
        if(unit->isDead()) continue;
        unit->render(window);
    }
		
    for (auto shell: Battlefield::getShells())
    {
        if(shell->isOver()) continue;
        shell->render(window);
    }
        
}



