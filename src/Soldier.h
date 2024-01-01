#ifndef SOLDIER
#define SOLDIER

#include "MilitaryUnit.h"
#include "Movable.h"
#include "Rotatable.h"

namespace sfGame
{


class Soldier: public MilitaryUnit
{
    public:
        Soldier(Side side, sf::Sprite sprite, float HP, float FOV, float DEF, float velocity);
        ~Soldier();
        void handleInput(sf::RenderWindow &window){}
        void update(sf::Time delta);
        void move();
        void setRoute(const Route &route);
        bool rotate();

    private:
        Movable *moveBehavior;
        Rotatable *rotateBehavior;
        sf::Vector2f destination;
};

}

#endif