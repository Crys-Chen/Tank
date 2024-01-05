#ifndef BATTLEFIELD
#define BATTLEFIELD
#include <iostream>
#include <assert.h>
#include <map>

#include "ThreadPool.h"
#include "MilitaryUnit.h"
#include "Shell.h"
// #include "Player.h"
// #include "Tower.h"
// #include "Soldier.h"
#include <vector>
#include <algorithm>

namespace sfGame
{
// class MilitaryUnit;
// typedef std::vector<MilitaryUnit*> Units;
typedef std::vector<std::vector<float>> Distance;


class Battlefield
{
    public:
        Battlefield();

        ~Battlefield();

        static float calDistance(sf::Vector2f unit1, sf::Vector2f unit2);

        static float getDistance(const MilitaryUnit *unit1, const MilitaryUnit *unit2);

        static bool checkCollision(MilitaryUnit *unit, sf::Vector2f &collisionObj);

        static void registerUnit(MilitaryUnit* unit);

        static void removeUnit(MilitaryUnit* unit);

        static void registerShell(Shell* shell);

        static void removeShell(Shell* shell);

        static Units& getUnits();

        static Shells& getShells();

        static bool isOver();

        static Side getWinner();

        static void update(sf::Time delta);

        static Battlefield *instance;

        // static void generateSoldiers(sf::Time delta, Nexus *blueNexus, Nexus *redNexus);

    
    private:
        Distance distance;
        Units units;
        Units deadUnits;
        Shells shells;
        Shells overShells;
        
        bool gameOver;
        Side winner;

        static bool checkUnitCollison(const MilitaryUnit *unit1, const MilitaryUnit *unit2);
        static bool checkObstacleCollison(const sf::Sprite &sprite1, sf::Vector2f &collisionObj);
        static void unitUpdate(MilitaryUnit *unit, sf::Time delta);
        static void shellUpdate(Shell *shell);
};

}

#endif