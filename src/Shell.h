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
        Shell(ShellSize size, const MilitaryUnit &attacker, MilitaryUnit *target, int ATK);
        void update();
        bool isOver(); //完成轰炸任务
        bool attack(); //冲！
        void hurt(); //造成伤害
        void render(sf::RenderWindow& window);

    private:
        sf::Sprite sprite;
        MilitaryUnit *target; //攻击目标
        int damage; //预期造成的伤害
        bool hit; //击中标志
};

typedef std::vector<Shell*> Shells;

}



#endif
