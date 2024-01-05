#ifndef SOLDIER
#define SOLDIER

#include "MilitaryUnit.h"
#include "Movable.h"
#include "Rotatable.h"
#include "Detect.h"
#include "Attack.h"

namespace sfGame
{


class Soldier: public MilitaryUnit
{
    public:
        Soldier(Side side, sf::Sprite sprite, int HP, int ATK, float attackRange, sf::Time attackInterval, float FOV, float velocity);
        ~Soldier();
        void handleInput(sf::RenderWindow &window){}
        void update(sf::Time delta);
        void move();
        bool detect();
        bool attack(sf::Time delta);
        void setRoute(const Route &route);
        bool rotate();
        Type getType() const;

    private:
        // Movable *moveBehavior;
        // Rotatable *rotateBehavior;
        // Detect *detectBehavior; 
        // sf::Vector2f destination;
};

}

#endif