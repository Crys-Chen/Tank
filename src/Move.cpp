#include "Move.h"
// #include "Game.h"

#include <cmath>
#include <iostream>

using namespace sfGame;

extern Battlefield battlefield;


void PlayerMove::move(MilitaryUnit &unit, sf::Vector2f &destination)
{
    sf::Sprite& sprite = unit.getSprite();
    auto currentPos = sprite.getPosition();

    if(destination == unit.getPos()) return;

    if(Battlefield::checkCollision(&unit, destination))
    {
        float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                    +(destination.y-currentPos.y)*(destination.y-currentPos.y));//必须先把double转成float
        if(length == 0) return;
        auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
        auto xOffset = direction.x*velocity;
        auto yOffset = direction.y*velocity;
        currentPos.x -= xOffset;
        currentPos.y -= yOffset;
        sprite.setPosition(currentPos);
        destination = currentPos; //退完就别动了
        return;
    }

   
    float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                +(destination.y-currentPos.y)*(destination.y-currentPos.y));//必须先把double转成float
    if(length == 0) return;

    auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
    auto xOffset = direction.x*velocity;
    auto yOffset = direction.y*velocity;
    
    auto distance = currentPos - destination;
    
    if(abs(distance.x) > abs(xOffset))
        currentPos.x += xOffset;
    else 
        currentPos.x = destination.x;
    if(abs(distance.y) > abs(yOffset))
        currentPos.y += yOffset;
    else 
        currentPos.y = destination.y;
    sprite.setPosition(currentPos);
}

void SoldierMove::setRoute(const Route &route)
{
    this->route = route;
}

void SoldierMove::updateDest(const MilitaryUnit &unit, sf::Vector2f &destination)
{
    if(unit.getTarget() == NULL)
    {
        assert(route.size() != 0);
        for(auto i : route)
        {
            if(unit.getSide() == Side::Blue)
            {
                if(i.y > unit.getPos().y)
                {
                    destination = i;
                    return;
                }
            }
            else if(unit.getSide() == Side::Red)
            {
                if(i.y < unit.getPos().y)
                {
                    destination = i;
                    return;
                }
            }

        }
    }
}

void SoldierMove::move(MilitaryUnit &unit, sf::Vector2f &destination)
{
    updateDest(unit, destination);
    if(destination == unit.getPos()) return;
    // std::cout<<destination.x<<","<<destination.y<<std::endl;

    sf::Sprite& sprite = unit.getSprite();
    auto currentPos=sprite.getPosition();

    if(Battlefield::checkCollision(&unit, destination))
    {
        float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                    +(destination.y-currentPos.y)*(destination.y-currentPos.y));
        if(length == 0) return;
        auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
        auto xOffset = direction.x*velocity;
        auto yOffset = direction.y*velocity;
        currentPos.x -= xOffset;
        currentPos.y -= yOffset;
        sprite.setPosition(currentPos);
        destination = currentPos; //退完就别动了
        return;
    }

   
    float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                +(destination.y-currentPos.y)*(destination.y-currentPos.y));//必须先把double转成float
    if(length == 0) return;

    auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
    auto xOffset = direction.x*velocity;
    auto yOffset = direction.y*velocity;
    
    auto distance = currentPos - destination;
    if(abs(distance.x) > abs(xOffset))
        currentPos.x += xOffset;
    else 
        currentPos.x = destination.x;

    if(abs(distance.y) > abs(yOffset))
        currentPos.y += yOffset;
    else 
        currentPos.y = destination.y;

    sprite.setPosition(currentPos);

}