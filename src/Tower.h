#ifndef TOWER
#define TOWER

#include "Parameters.h"
#include "Soldier.h"
#include "Rotatable.h"
#include "Detect.h"
#include "AssetManager.h"

namespace sfGame{



class Tower: public MilitaryUnit
{
    public:
        Tower(Side side, sf::Sprite sprite, int HP, int ATK, float FOV);
        ~Tower();
        void move() {}
        Type getType() const;
        bool rotate();
        bool detect();
        void update(sf::Time delta);
        void handleInput(sf::RenderWindow &window){}
    protected:
        // Rotatable *rotateBehavior;
        // Detect *detectBehavior;
        // sf::Vector2f destination;

};

class Nexus: public Tower
{
    public:
        Nexus(Side side, sf::Sprite sprite, int HP, int ATK, float FOV);
        ~Nexus();
        // void update(sf::Time delta)
        void move(){}
        void handleInput(sf::RenderWindow &window){}
        void generateSoldiers();
        void generate();
    private:
        // sf::Time generateInterval;
        sf::Sprite midSoldiers[3];
        sf::Sprite leftSoldiers[3];
        sf::Sprite rightSoldiers[3];
        Route midRoute[3];
        Route leftRoute[3];
        Route rightRoute[3]; 
        
};



}

#endif
