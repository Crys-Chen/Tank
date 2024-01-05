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
        Attack(ShellSize size, int ATK);
        void attack(const MilitaryUnit &attacker, MilitaryUnit &unit);
        // void setShell();
    private:
        ShellSize size;
        float ATK;

};

}

#endif