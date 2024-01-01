#include "Tower.h"

using namespace sfGame;

extern AssetManager manager;

const float soldierFOV = 30;

Tower::Tower(Side side, sf::Sprite sprite, float HP, float FOV, float DEF):
    MilitaryUnit(side, Type::tower, sprite, HP, FOV, DEF) 
{
    rotateBehavior = new Rotatable(1.5);
    detectBehavior = new LockDetect(FOV);

}

Tower::~Tower()
{
    delete rotateBehavior;
    delete detectBehavior;
}

bool Tower::detect()
{
    MilitaryUnit *target = NULL;
    if(detectBehavior->detect(this, target))
    {
        // std::cout<<"detect enemy!"<<std::endl;
        destination = target->getPos();
        return true;
    }
    return false;
}

void Tower::update(sf::Time delta)
{
    if(detect())
        rotate();
    else//归位
    {
        if(side == Side::Blue)
            destination = getPos() + sf::Vector2f(0, 100);
        else
            destination = getPos() - sf::Vector2f(0, 100);
        rotate();
    }
        
}

bool Tower::rotate()
{
    return rotateBehavior->rotate(*this, destination);
}

Nexus::Nexus(Side side, sf::Sprite sprite, float HP, float FOV, float DEF, sf::Time interval):
    Tower(side, sprite, HP, FOV, DEF),
    generateInterval(interval)
{

if(side == Side::Blue)
{
    //middle
    midRoute[0] = {sf::Vector2f(640, 197), sf::Vector2f(640, 738), sf::Vector2f(640, 1440), sf::Vector2f(640, 1950), sf::Vector2f(640, 2683)};
    // midRoute[1] = {sf::Vector2f(700, 197), sf::Vector2f(700, 738), sf::Vector2f(700, 1440), sf::Vector2f(700, 1950), sf::Vector2f(700, 2683)};
    midRoute[1] = midRoute[0];
    midRoute[2] = midRoute[0];
    
    for(size_t i = 0; i < midRoute[0].size(); i++)
    {
        midRoute[1][i].x -= 60;
        midRoute[2][i].x += 60;
    }

    

    midSoldiers[0].setTexture(AssetManager::getTexture("./pictures/blueSoldier1.png"));
    midSoldiers[0].setScale(1.5,1.5);
    midSoldiers[0].setOrigin(sf::Vector2f(30,30));
    midSoldiers[0].setPosition(midRoute[0][0]);

    midSoldiers[1].setTexture(AssetManager::getTexture("./pictures/blueSoldier3.png"));
    midSoldiers[1].setScale(1.5,1.5);
    midSoldiers[1].setOrigin(sf::Vector2f(22.5,22.5));
    midSoldiers[1].setPosition(midRoute[1][0]);

    midSoldiers[2] = midSoldiers[1];
    midSoldiers[2].setPosition(midRoute[2][0]);
    
//left
    leftRoute[0] = {sf::Vector2f(548, 84), sf::Vector2f(105, 289), sf::Vector2f(105, 1440), sf::Vector2f(105, 2591), sf::Vector2f(548, 2796)};
    leftRoute[1] = leftRoute[0];
    leftRoute[2] = leftRoute[0];

    leftRoute[1][0].y -= 60;
    leftRoute[2][0].y += 60;

    for(int i = 1; i < 4; i++)
    {
        leftRoute[1][i].x -= 60;
        leftRoute[2][i].x += 60;
    }

    leftRoute[1][4].y += 60;
    leftRoute[2][4].y -= 60;

    leftSoldiers[0].setTexture(AssetManager::getTexture("./pictures/blueSoldier2.png"));
    leftSoldiers[0].setScale(1.8,1.8);
    leftSoldiers[0].setOrigin(sf::Vector2f(25,25));
    leftSoldiers[0].setPosition(leftRoute[0][0]);

    leftSoldiers[1] = midSoldiers[1];
    leftSoldiers[1].setPosition(leftRoute[1][0]);

    leftSoldiers[2] = midSoldiers[1];
    leftSoldiers[2].setPosition(leftRoute[2][0]);

//right
    rightRoute[0] = {sf::Vector2f(755, 84), sf::Vector2f(1175, 289), sf::Vector2f(1175, 1440), sf::Vector2f(1175, 2591), sf::Vector2f(755, 2796)};
    rightRoute[1] = rightRoute[0];
    rightRoute[2] = rightRoute[0];

    rightRoute[1][0].y += 60;
    rightRoute[2][0].y -= 60;

    for(int i = 1; i < 4; i++)
    {
        rightRoute[1][i].x -= 60;
        rightRoute[2][i].x += 60;
    }

    rightRoute[1][4].y -= 60;
    rightRoute[2][4].y += 60;


    rightSoldiers[0].setTexture(AssetManager::getTexture("./pictures/blueSoldier2.png"));
    rightSoldiers[0].setScale(1.8,1.8);
    rightSoldiers[0].setOrigin(sf::Vector2f(25,25));
    rightSoldiers[0].setPosition(rightRoute[0][0]);

    rightSoldiers[1] = midSoldiers[1];
    rightSoldiers[1].setPosition(rightRoute[1][0]);

    rightSoldiers[2] = midSoldiers[1];
    rightSoldiers[2].setPosition(rightRoute[2][0]);
}




else if(side == Side::Red)
{
    //middle
    midRoute[0] = {sf::Vector2f(640, 2683), sf::Vector2f(640, 2142), sf::Vector2f(640, 1440), sf::Vector2f(640, 930), sf::Vector2f(640, 197)};
    // midRoute[1] = {sf::Vector2f(700, 197), sf::Vector2f(700, 738), sf::Vector2f(700, 1440), sf::Vector2f(700, 1950), sf::Vector2f(700, 2683)};
    midRoute[1] = midRoute[0];
    midRoute[2] = midRoute[0];
    
    for(size_t i = 0; i < midRoute[0].size(); i++)
    {
        midRoute[1][i].x -= 60;
        midRoute[2][i].x += 60;
    }

    

    midSoldiers[0].setTexture(AssetManager::getTexture("./pictures/redSoldier1.png"));
    midSoldiers[0].setScale(1.5,1.5);
    midSoldiers[0].setOrigin(sf::Vector2f(30,30));
    midSoldiers[0].setPosition(midRoute[0][0]);

    midSoldiers[1].setTexture(AssetManager::getTexture("./pictures/redSoldier3.png"));
    midSoldiers[1].setScale(1.5,1.5);
    midSoldiers[1].setOrigin(sf::Vector2f(22.5,22.5));
    midSoldiers[1].setPosition(midRoute[1][0]);

    midSoldiers[2] = midSoldiers[1];
    midSoldiers[2].setPosition(midRoute[2][0]);
    
//left
    leftRoute[0] = {sf::Vector2f(548, 2796), sf::Vector2f(105, 2591), sf::Vector2f(105, 1440), sf::Vector2f(105, 289), sf::Vector2f(548, 84)};
    leftRoute[1] = leftRoute[0];
    leftRoute[2] = leftRoute[0];

    leftRoute[1][0].y += 60;
    leftRoute[2][0].y -= 60;

    for(int i = 1; i < 4; i++)
    {
        leftRoute[1][i].x -= 60;
        leftRoute[2][i].x += 60;
    }

    leftRoute[1][4].y -= 60;
    leftRoute[2][4].y += 60;

    leftSoldiers[0].setTexture(AssetManager::getTexture("./pictures/redSoldier2.png"));
    leftSoldiers[0].setScale(1.8,1.8);
    leftSoldiers[0].setOrigin(sf::Vector2f(25,25));
    leftSoldiers[0].setPosition(leftRoute[0][0]);

    leftSoldiers[1] = midSoldiers[1];
    leftSoldiers[1].setPosition(leftRoute[1][0]);

    leftSoldiers[2] = midSoldiers[1];
    leftSoldiers[2].setPosition(leftRoute[2][0]);

//right
    rightRoute[0] = {sf::Vector2f(755, 2796), sf::Vector2f(1175, 2591), sf::Vector2f(1175, 1440), sf::Vector2f(1175, 289), sf::Vector2f(755, 84)};
    rightRoute[1] = rightRoute[0];
    rightRoute[2] = rightRoute[0];

    rightRoute[1][0].y -= 60;
    rightRoute[2][0].y += 60;

    for(int i = 1; i < 4; i++)
    {
        rightRoute[1][i].x -= 60;
        rightRoute[2][i].x += 60;
    }

    rightRoute[1][4].y += 60;
    rightRoute[2][4].y -= 60;


    rightSoldiers[0].setTexture(AssetManager::getTexture("./pictures/redSoldier2.png"));
    rightSoldiers[0].setScale(1.8,1.8);
    rightSoldiers[0].setOrigin(sf::Vector2f(25,25));
    rightSoldiers[0].setPosition(rightRoute[0][0]);

    rightSoldiers[1] = midSoldiers[1];
    rightSoldiers[1].setPosition(rightRoute[1][0]);

    rightSoldiers[2] = midSoldiers[1];
    rightSoldiers[2].setPosition(rightRoute[2][0]);
}


}

Nexus::~Nexus()
{
    delete rotateBehavior;
    delete detectBehavior;
}

void Nexus::generateSoldiers()
{
    auto soldier = new Soldier(side, midSoldiers[0],1,soldierFOV,1,0.75);
    soldier->setRoute(midRoute[0]);
    Battlefield::registerUnit(soldier);

    soldier = new Soldier(side, midSoldiers[1],1,soldierFOV,1,0.75);
    soldier->setRoute(midRoute[1]);
    Battlefield::registerUnit(soldier);

    soldier = new Soldier(side, midSoldiers[2],1,soldierFOV,1,0.75);
    soldier->setRoute(midRoute[2]);
    Battlefield::registerUnit(soldier);

    soldier = new Soldier(side, leftSoldiers[0],1,soldierFOV,1,1);
    soldier->setRoute(leftRoute[0]);
    Battlefield::registerUnit(soldier);

    soldier = new Soldier(side, leftSoldiers[1],1,soldierFOV,1,1.05);
    soldier->setRoute(leftRoute[1]);
    Battlefield::registerUnit(soldier);

    soldier = new Soldier(side, leftSoldiers[2],1,soldierFOV,1,0.95);
    soldier->setRoute(leftRoute[2]);
    Battlefield::registerUnit(soldier);


    soldier = new Soldier(side, rightSoldiers[0],1,soldierFOV,1,1);
    soldier->setRoute(rightRoute[0]);
    Battlefield::registerUnit(soldier);

    soldier = new Soldier(side, rightSoldiers[1],1,soldierFOV,1,0.95);
    soldier->setRoute(rightRoute[1]);
    Battlefield::registerUnit(soldier);

    soldier = new Soldier(side, rightSoldiers[2],1,soldierFOV,1,1.05);
    soldier->setRoute(rightRoute[2]);
    Battlefield::registerUnit(soldier);

    
    

}