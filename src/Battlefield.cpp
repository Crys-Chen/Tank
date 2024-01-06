#include "Battlefield.h"


using namespace sfGame;

Battlefield* Battlefield::instance = nullptr;
extern ThreadPool threadPool;

Battlefield::Battlefield()
{
    assert(instance==nullptr);
    // if(instance != nullptr) return;
    instance=this;
    distance.resize(units.size());
    shells.resize(0);
    units.resize(0);
    shells.resize(0);
    overShells.resize(0);
    deadUnits.resize(0);

    gameOver = false;
    for(size_t i = 0; i < units.size(); i++)
    {
        distance[i].resize(units.size());
        for(size_t j = 0; j < units.size(); j++)
            distance[i][j] = calDistance(units[i]->getPos(), units[j]->getPos());
    }
}

Battlefield::~Battlefield()
{
    delete instance;
    for(auto i : units)
        delete i;
    for(auto i : shells)
        delete i;
}

// void Battlefield::setInstance(Battlefield *instance)
// {
//     static bool already = false;
//     if(already == true) return;
//     if(instance != NULL)
//     {
//         Battlefield::instance = instance;
//         already = true;
//     }
// }

float Battlefield::calDistance(sf::Vector2f unit1, sf::Vector2f unit2)
{
    auto distanceX = unit1.x - unit2.x;
    auto distanceY = unit1.y - unit2.y;
    return sqrt(distanceX * distanceX + distanceY * distanceY);
}

float Battlefield::getDistance(const MilitaryUnit *unit1, const MilitaryUnit *unit2) 
{
    // assert(!unit1->isDead() && !unit2->isDead());
    if(unit1->isDead() || unit2->isDead()) 
        return 1E6;
    int index1 = std::find(instance->units.begin(), instance->units.end(), unit1) - instance->units.begin();
    int index2 = std::find(instance->units.begin(), instance->units.end(), unit2) - instance->units.begin();
    return instance->distance[index1][index2];
}

bool Battlefield::checkObstacleCollison(const sf::Sprite &sprite, sf::Vector2f &collisionObj)
{
    sf::Rect<float> obstacle[8];
    obstacle[0].left = 353;
    obstacle[0].top = 308;
    obstacle[0].width = 100;
    obstacle[0].height = 262;

    obstacle[1].left = 249;
    obstacle[1].top = 462;
    obstacle[1].width = 130;
    obstacle[1].height = 100;

    obstacle[2].left = 819;
    obstacle[2].top = 316;
    obstacle[2].width = 100;
    obstacle[2].height = 262;

    obstacle[3].left = 934;
    obstacle[3].top = 478;
    obstacle[3].width = 90;
    obstacle[3].height = 100;

    obstacle[4].left = 254;
    obstacle[4].top = 2301;
    obstacle[4].width = 202;
    obstacle[4].height = 100;

    obstacle[5].left = 371;
    obstacle[5].top = 2428;
    obstacle[5].width = 90;
    obstacle[5].height = 100;


    obstacle[6].left = 828;
    obstacle[6].top = 2305;
    obstacle[6].width = 100;
    obstacle[6].height = 262;


    
    obstacle[7].left = 924;
    obstacle[7].top = 2310;
    obstacle[7].width = 100;
    obstacle[7].height = 110;



    for(int i = 0; i < 8; i++)
    {
        if(sprite.getGlobalBounds().intersects(obstacle[i]))
        {
            collisionObj = sf::Vector2f(obstacle[i].left + obstacle[i].width/2, obstacle[i].top + obstacle[i].height/2);
            return true;
        }
            
    }
    return false;
     
}

bool Battlefield::checkUnitCollison(const MilitaryUnit *unit1, const MilitaryUnit *unit2)
{
    //玩家和小兵可以重叠，不然太挤
    if(unit1->getType() == Type::player || unit2->getType() == Type::player) 
    {
        if(unit1->getType() == soldier || unit2->getType() == Type::soldier)
            return false;
    } 
    //同阵营小兵可以重叠，不然太挤
    if(unit1->getType() == soldier && unit2->getType() == Type::soldier && unit1->getSide() == unit2->getSide())
        return false;


    auto r1 = unit1->getRadius();
    auto r2 = unit2->getRadius();
    return getDistance(unit1, unit2) < r1 + r2;
}

bool Battlefield::checkCollision(MilitaryUnit *unit, sf::Vector2f &collisionObj)
{
    if(checkObstacleCollison(unit->getSprite(), collisionObj)) 
    {
        // std::cout<<"hit obstacle!"<<std::endl;
        return true;
    }
        
    for(auto i : instance->units)
    {
        if(i == unit || i->isDead())
            continue;
        if(checkUnitCollison(unit, i))
        {
            // std::cout<<"hit unit!"<<std::endl;
            collisionObj = i->getSprite().getPosition();
            return true;
        }
    }
    
    return false;
}

void unitUpdate(MilitaryUnit *unit, sf::Time delta)
{
    unit->update(delta);
}

void shellUpdate(Shell *shell)
{
    shell->update();
}


void Battlefield::update(sf::Time delta)
{
    instance->distance.clear();
    instance->distance.resize(instance->units.size());
    for(size_t i = 0; i < instance->units.size(); i++)
    {
        if(instance->units[i]->isDead()) continue;
        instance->distance[i].resize(instance->units.size());
        for(size_t j = 0; j < instance->units.size(); j++)
        {
            if(instance->units[j]->isDead()) continue;
            instance->distance[i][j] = calDistance(instance->units[i]->getPos(), instance->units[j]->getPos());
        }
    }

    for(auto unit: instance->units)
    {
        if(unit->isDead()) continue;
        threadPool.submit(unitUpdate,unit,delta);
    }

    for(auto shell: instance->shells)
    {
        if(shell->isOver()) continue;
        threadPool.submit(shellUpdate,shell);
        // shellUpdate(shell);
    }
    

    // ThreadPool pool(10);

    // for(size_t i = 0; i < instance->units.size(); i++)
    // {
    //     auto unit = instance->units[i];
    //     if(unit->isDead()) continue;
    //     // unitsFut.push_back(threadPool.submit(unitUpdate, unit, delta));
    //     unitUpdate(unit, delta);
    //     // if(unit->isDead())
    //     // {
    //         // instance->units.erase(Units::iterator(&instance->units[i]));
    //         // i--;
    //         // if(unit != NULL && unit->getType() != Type::player)
    //         //     delete unit;
    //     // }
    // }

    // for(size_t i = 0; i < instance->shells.size(); i++)
    // {
    //     auto shell = instance->shells[i];
    //     if(shell->isOver()) continue;
    //     // shellsFut.push_back(threadPool.submit(shellUpdate, shell));
    //     shellUpdate(shell);
    //     // if(shell->isOver())
    //     // {
    //     //     instance->shells.erase(Shells::iterator(&instance->shells[i]));
    //     //     i--;
    //     //     if(shell != NULL)
    //     //         delete shell;
    //     // }
    // }
    // for(auto shell: instance->shells)
    // {
    //     if(shell->isOver())
    //     {
    //         removeShell(shell);
    //         delete shell;
    //     }
    // }

    // for(size_t i = 0; i < instance->shells.size(); i++)
    // {
    //     auto shell = instance->shells[i];
    //     shellsFut[i].get();
    //     if(shell->isOver())
    //     {
    //         removeShell(shell);
    //         delete shell;
    //     }
    // }

    // for (auto unit : instance->units)
    // for(size_t i = 0; i < instance->units.size(); i++)
    // {
    //     auto unit = instance->units[i];
    //     unitsFut[i].get();
    //     if(unit->isDead())
    //     {
    //         removeUnit(unit);
    //         // auto isPlayer = dynamic_cast<Player*>(unit);
    //         // if(isPlayer == NULL) //除了玩家以外都是一次性耗材，直接delete掉。
    //         //     delete unit;
    //         if(unit->getType() != Type::player)
    //             delete unit;
    //     }
    // }

}



void Battlefield::registerUnit(MilitaryUnit* unit)
{
    assert(unit != NULL);
    // std::cout<<"register!"<<std::endl;
    instance->units.push_back(unit);
}


void Battlefield::registerShell(Shell* shell)
{
    assert(shell != NULL);
    instance->shells.push_back(shell);
}



// void Battlefield::removeUnit(MilitaryUnit* unit)
// {
//     assert(unit != NULL);
//     // for(auto i = instance->units.begin(); i != instance->units.end(); i++)
//     // {
//     //     if(*i == unit)
//     auto i = std::find(instance->units.begin(), instance->units.end(), unit);
//     instance->units.erase(i);
//     // }
// }

// void Battlefield::removeShell(Shell* shell)
// {
//     assert(shell != NULL);
//     for(auto i = instance->shells.begin(); i != instance->shells.end(); i++)
//     {
//         if(*i == shell)
//             instance->shells.erase(i);
//     }
// }

Units& Battlefield::getUnits()
{
    return instance->units;
}

Shells& Battlefield::getShells()
{
    return instance->shells;
}

