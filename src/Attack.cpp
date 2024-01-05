
#include "Attack.h"

using namespace sfGame;

extern Battlefield battlefield;

Attack::Attack(ShellSize size, int ATK, float attackRange, sf::Time attackInterval): 
    size(size), ATK(ATK), attackRange(attackRange), attackInterval(attackInterval)
{
    attackClock = sf::Time::Zero;
}


bool Attack::attack(MilitaryUnit &attacker, sf::Time delta)
{
    auto target = attacker.target;
    attackClock += delta;
    // std::cout<<attackClock.asSeconds()<<std::endl;
    // std::cout<<attackInterval.asSeconds()<<std::endl;
    // std::cout<<delta.asSeconds()<<std::endl;

    if(target == NULL) return false;
    if(Battlefield::getDistance(&attacker, target) > attackRange)
    {
        attacker.moveDest = target->getPos();
        return false;
    }


    if(attackClock > attackInterval)
    {
        attackClock = sf::Time::Zero;
        fire(attacker, *target);
        target = NULL;
    }

    attacker.moveDest = attacker.getPos();
    return true;
}

void Attack::fire(const MilitaryUnit &attacker, MilitaryUnit &unit)
{
    // auto DEF = unit.getDEF();
    auto shell = new Shell(size, attacker, &unit);
    Battlefield::registerShell(shell);
    
}


