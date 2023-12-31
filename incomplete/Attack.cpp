#include "Attack.h"

using namespace sfGame;

void ComputerAttack::attack(MilitaryUnit &enemy)
{
    sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

//少了一层，while目标在视野范围内
    sf::Time delta = clock.restart();
    timeSinceLastUpdate += delta;

    while (timeSinceLastUpdate > attackInterval)
    {
        timeSinceLastUpdate -= attackInterval;
        enemy.beingAttacked(ATK - enemy.getDEF());
    }
    
}