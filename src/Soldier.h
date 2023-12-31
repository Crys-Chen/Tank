#ifndef SOLDIER
#define SOLDIER

#include "MilitaryUnit.h"

namespace sfGame
{

class Soldier: public MilitaryUnit
{
    public:
        Soldier(Side side, sf::Sprite sprite, float HP, float FOV, float DEF):
            MilitaryUnit(side, sprite, HP, FOV, DEF) {};
        void handleInput(sf::RenderWindow &window){}
        void move(){}
};

}

#endif