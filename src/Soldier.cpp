#include "Soldier.h"

using namespace sfGame;

Soldier::Soldier(Side side, sf::Sprite sprite, float HP, float FOV, float DEF, float velocity):
    MilitaryUnit(side, Type::soldier, sprite, HP, FOV, DEF)
{
    moveBehavior = new SoldierMove(velocity);
    rotateBehavior = new Rotatable(1);
    destination = getPos();
}

Soldier::~Soldier()
{
    delete moveBehavior;
    delete rotateBehavior;
}

void Soldier::setRoute(const Route &route)
{
    moveBehavior->setRoute(route);
}

void Soldier::update(sf::Time delta)
{
    if(!rotate())
        move(); 
}

bool Soldier::rotate()
{
    // auto destination = getPos();
    return rotateBehavior->rotate(*this, destination);
}

void Soldier::move()
{
    // auto destination = getPos();
    moveBehavior->move(*this, destination);
}

