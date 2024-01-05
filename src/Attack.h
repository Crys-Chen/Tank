#ifndef ATTACK
#define ATTACK

#include "MilitaryUnit.h"
#include "Battlefield.h"
#include "Shell.h"

namespace sfGame
{
class Attack
{
    public:
        Attack(ShellSize size, int ATK, float attackRange, sf::Time attackInterval);
        bool attack(MilitaryUnit &attacker, sf::Time delta);
        void fire(const MilitaryUnit &attacker, MilitaryUnit &unit);

    private:
        ShellSize size;
        float ATK;
        float attackRange;
        sf::Time attackInterval;
        sf::Time attackClock;

};

}

#endif