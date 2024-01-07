#include "Soldier.h"

using namespace sfGame;
extern ThreadPool threadPool;

Soldier::Soldier(Side side, sf::Sprite sprite, int HP, int ATK, float attackRange, sf::Time attackInterval, float FOV, float velocity, float omega):
    MilitaryUnit(side, sprite, HP)
{
    moveBehavior = new SoldierMove(velocity);
    rotateBehavior = new Rotate(omega);
    detectBehavior = new MinDetect(FOV);
    attackBehavior = new Attack(ShellSize::small, ATK, attackRange, attackInterval);
    moveDest = getPos();
    if(!moveBehavior || !rotateBehavior || !detectBehavior || !attackBehavior)
        std::cout<<"new error!"<<std::endl;
}

Soldier::~Soldier()
{
    delete moveBehavior;
    delete rotateBehavior;
    delete detectBehavior;
    delete attackBehavior;
}

Type Soldier::getType() const
{
    return Type::soldier;
}

void Soldier::setRoute(const Route &route)
{
    moveBehavior->setRoute(route);
}



void Soldier::update(sf::Time delta)
{
    if(isDead()) return;
    detect();
    // threadPool.submit(soldierDetect, this);
    if(!rotate())
    {
        if(!attack(delta))
            move();
    }     
}

bool Soldier::attack(sf::Time delta)
{
    return attackBehavior->attack(*this, delta);
}

bool Soldier::rotate()
{
    // auto moveDest = getPos();
    return rotateBehavior->rotate(*this, rotateDest);
}

void Soldier::move()
{
    moveBehavior->move(*this, moveDest);
}

bool Soldier::detect()
{
    if(detectBehavior->detect(this, target))
    {
        moveDest = getPos();
        rotateDest = target->getPos();
        return true;
    }
    target = NULL;
    rotateDest = moveDest;
    return false;
}

