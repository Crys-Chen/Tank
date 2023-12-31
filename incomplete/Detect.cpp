#include "Detect.h"

using namespace sfGame;

float Detect::getDistance(sf::Vector2f unit1, sf::Vector2f unit2)
{
    auto distanceX = unit1.x - unit2.x;
    auto distanceY = unit1.y - unit2.y;
    return sqrt(distanceX * distanceX + distanceY * distanceY);
}


bool Detect::see(sf::Vector2f unit1, sf::Vector2f unit2)
{
    return getDistance(unit1, unit2) < FOV;
}

void Detect::setPos(sf::Vector2f position)
{
    this->position = position;
}

void Detect::update(const Units &enemies)
{
    sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

//少了一层
    sf::Time delta = clock.restart();
    timeSinceLastUpdate += delta;

    while (timeSinceLastUpdate > detectInterval)
    {
        timeSinceLastUpdate -= detectInterval;
        detect(enemies);
    }
}

void LockDetect::detect(const Units &enemies)
{
    if(target != NULL && see(target->getPos(), position))
        return;
    
    for (auto it = enemies.begin(); it != enemies.end(); it++)
    {
        if(see((*it)->getPos(), position)) //检测到了敌人
        {
            target = *it;
            return ;
        }
    }
}


void MinDetect::detect(const Units &enemies )
{
    std::priority_queue<Object, std::vector<Object>, cmp> enemiesHeap;

    for (auto it = enemies.begin(); it != enemies.end(); it++)
    {
        if(see((*it)->getPos(), position)) //检测到了敌人
        {
            Object object(*it, getDistance((*it)->getPos(), position));
            enemiesHeap.push(object);
        }
    }

    target = enemiesHeap.top().target;
}
