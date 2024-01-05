#include "Soldier.h"

using namespace sfGame;

Soldier::Soldier(Side side, sf::Sprite sprite, int HP, int ATK, float attackRange, sf::Time attackInterval, float FOV, float velocity):
    MilitaryUnit(side, sprite, HP, ATK)
{
    moveBehavior = new SoldierMove(velocity);
    rotateBehavior = new Rotatable(1);
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
    if(!rotate())
    {
        if(!attack(delta))
            move();
    }     
}

bool Soldier::attack(sf::Time delta)
{
    // attackClock += delta;

    // if(target == NULL) return false;
    // if(Battlefield::getDistance(this, target) > attackRange)
    // {
    //     moveDest = target->getPos();
    //     return false;
    // }

    // if(attackClock > attackInterval)
    // {
    //     attackClock = sf::Time::Zero;
    //     attackBehavior->attack(*this, *target);
    //     target = NULL;
    // }

    // moveDest = getPos();
    // return true;
    return attackBehavior->attack(*this, delta);
}

bool Soldier::rotate()
{
    // auto moveDest = getPos();
    return rotateBehavior->rotate(*this, rotateDest);
}

void Soldier::move()
{
    // auto moveDest = getPos();
    moveBehavior->move(*this, moveDest);
}

bool Soldier::detect()
{
    if(detectBehavior->detect(this, target))
    {
        // std::cout<<"detect enemy!"<<std::endl;
        // moveDest = target->getPos();
        moveDest = getPos();
        rotateDest = target->getPos();
        return true;
    }
    rotateDest = moveDest;
    return false;
}

