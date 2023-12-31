#ifndef TOWER
#define TOWER

#include "Soldier.h"

namespace sfGame{



class Tower: public MilitaryUnit
{
    public:
        Tower(Side side, sf::Sprite sprite, float HP, float FOV, float DEF):
            MilitaryUnit(side, sprite, HP, FOV, DEF) {}
        ~Tower() = default;
        void move() {}
        void update(sf::Time delta){}
        void handleInput(sf::RenderWindow &window){}
    private:
};

class Nexus: public Tower
{
    public:
        Nexus(Side side, sf::Sprite sprite, float HP, float FOV, float DEF, sf::Time interval = sf::seconds(1)):
            Tower(side, sprite, HP, FOV, DEF),
            generateInterval(interval){}
        ~Nexus() = default;
        void update(sf::Time delta){}
        void move(){}
        void handleInput(sf::RenderWindow &window){}
        void generateSoldiers(Soldier *soldiers, sf::Time delta) {}
    private:
        sf::Time generateInterval;
        
};

}

#endif
