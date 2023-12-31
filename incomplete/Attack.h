#ifndef ATTACK
#define ATTACK
#include "MilitaryUnit.h"

namespace sfGame
{
class Attack
{
    public:
        Attack(float ATK, float attackRange, sf::Time attackInterval):
            ATK(ATK), attackRange(attackRange), attackInterval(attackInterval) {}
        virtual void attack(MilitaryUnit &enemy) = 0;
    protected:
        float ATK; //攻击力
        float attackRange; //攻击半径
        sf::Time attackInterval; //攻击时间间隔

};

class ComputerAttack: public Attack
{
    public:
        ComputerAttack(float ATK, float attackRange, sf::Time attackInterval):
            Attack(ATK, attackRange, attackInterval) {}
        void attack(MilitaryUnit &enemy);
    
};

class Spell
{
    public:
        virtual void passiveSpell() = 0;
        virtual void activeSpell() = 0;
};

}

#endif