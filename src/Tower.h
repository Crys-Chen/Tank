#ifndef TOWER
#define TOWER

#include "Soldier.h"
#include "AssetManager.h"

namespace sfGame{



class Tower: public MilitaryUnit
{
    public:
        Tower(Side side, sf::Sprite sprite, float HP, float FOV, float DEF):
            MilitaryUnit(side, Type::tower, sprite, HP, FOV, DEF) {}
        ~Tower() = default;
        void move() {}
        void update(sf::Time delta){}
        void handleInput(sf::RenderWindow &window){}
    private:
};

class Nexus: public Tower
{
    public:
        Nexus(Side side, sf::Sprite sprite, float HP, float FOV, float DEF, sf::Time interval = sf::seconds(1));
        ~Nexus() = default;
        void update(sf::Time delta){}
        void move(){}
        void handleInput(sf::RenderWindow &window){}
        void generateSoldiers();
    private:
        sf::Time generateInterval;
        sf::Sprite midSoldiers[3];
        sf::Sprite leftSoldiers[3];
        sf::Sprite rightSoldiers[3];
        Route midRoute[3];
        Route leftRoute[3];
        Route rightRoute[3]; 
        
};



}

#endif
