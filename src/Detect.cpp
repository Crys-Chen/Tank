#include "Detect.h"

using namespace sfGame;

extern Battlefield battlefield;

bool LockDetect::detect(const Units &enemies, MilitaryUnit &object)
{
    if(Battlefield::)
    
    for (auto it = enemies.begin(); it != enemies.end(); it++)
    {
        if(see((*it)->getPos(), position)) //检测到了敌人
        {
            target = *it;
            return ;
        }
    }
}


void MinDetect::detect(const Units &enemies )
{
    std::priority_queue<Object, std::vector<Object>, cmp> enemiesHeap;

    for (auto it = enemies.begin(); it != enemies.end(); it++)
    {
        if(see((*it)->getPos(), position)) //检测到了敌人
        {
            Object object(*it, getDistance((*it)->getPos(), position));
            enemiesHeap.push(object);
        }
    }

    target = enemiesHeap.top().target;
}
