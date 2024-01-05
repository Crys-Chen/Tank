
#include "Attack.h"

using namespace sfGame;

extern Battlefield battlefield;

Attack::Attack(ShellSize size, int ATK): size(size), ATK(ATK)
{
}

void Attack::attack(const MilitaryUnit &attacker, MilitaryUnit &unit)
{
    // auto DEF = unit.getDEF();
    auto shell = new Shell(size, attacker, &unit);
    Battlefield::registerShell(shell);
    
}


