#ifndef SHELL
#define SHELL

#include "MilitaryUnit.h"
#include "AssetManager.h"
#include "Parameters.h"

namespace sfGame
{

enum ShellSize
{
    large,
    medium,
    small
};

class Shell
{
    public:
        Shell(ShellSize size, const MilitaryUnit &attacker, MilitaryUnit *target);
        void update();
        bool isOver();
        bool attack();
        void hurt();
        void render(sf::RenderWindow& window);

    private:
        sf::Sprite sprite;
        MilitaryUnit *target;
        int damage;
        bool hit;
};

typedef std::vector<Shell*> Shells;

}



#endif
