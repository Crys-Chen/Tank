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
        ShellSize size; //炮弹类型
        float ATK; //攻击力
        float attackRange; //攻击距离
        sf::Time attackInterval; //攻击间隔（攻速）
        sf::Time attackClock; //用于判断是否满足攻击间隔

};

}

#endif