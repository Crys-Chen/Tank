#include "Detect.h"

using namespace sfGame;

extern Battlefield battlefield;

LockDetect::LockDetect(float FOV):
   Detect(FOV), random(time(NULL))
{

}

bool LockDetect::detect(MilitaryUnit *self, MilitaryUnit *&target)
{
    auto units = Battlefield::getUnits();

    if((target != NULL) && (Battlefield::getDistance(self, target) < FOV)) //目标还在视野范围内
        return true;
    
    Units enemiesInVision;
    enemiesInVision.clear();
    for (auto i : units)
    {
        if(i->isDead()) 
            continue;
        if(i->getSide() == self->getSide())  //大水淹了龙王庙
            continue;
        if(Battlefield::getDistance(self, i) < FOV) //检测到了敌人
            enemiesInVision.push_back(i);
    }

    if(enemiesInVision.empty()) 
    {
        target = NULL;
        return false;
    }
        
    if(enemiesInVision.size() == 1)
        target = enemiesInVision[0];
    else
    {
        do
        {
            std::uniform_int_distribution<int> distribution(0, enemiesInVision.size()-1); //int随机数范围是闭区间，最后得-1
            target = enemiesInVision[distribution(random)];
            
        }while(target->getType() != Type::player);
    }

    return true;
    

}


bool MinDetect::detect(MilitaryUnit *self, MilitaryUnit *&target)
{
    auto units = Battlefield::getUnits();

    std::priority_queue<Enemy, std::vector<Enemy>, cmp> enemiesInVision;

    for (auto i : units)
    {
        if(i->isDead()) 
            continue;
        if(i->getSide() == self->getSide())  //大水淹了龙王庙
            continue;
        auto distance = Battlefield::getDistance(self, i);
        if(distance < FOV) //检测到了敌人
            enemiesInVision.push(Enemy(i,distance));
    }

    if(enemiesInVision.empty()) 
    {
        target = NULL;
        return false;
    }
    
    target = enemiesInVision.top().target;
    return true;
}

