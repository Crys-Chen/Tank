#ifndef ROTATABLE
#define ROTATABLE

#include <SFML/Graphics.hpp>
#include <cmath>
#include "MilitaryUnit.h"

namespace sfGame
{

class Rotatable
{
    public:
        Rotatable(float omega): omega(omega) {}
        bool rotate(MilitaryUnit &unit, const sf::Vector2f &destination);
    protected:
        float omega;
};

// class PlayerRotate: public Rotatable
// {
//     public:
//         PlayerRotate(float omega): Rotatable(omega) {}
//         bool rotate(sf::Sprite &sprite, const sf::Vector2f &destination);
// };

}

#endif