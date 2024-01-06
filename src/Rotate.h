#ifndef ROTATABLE
#define ROTATABLE

#include <SFML/Graphics.hpp>
#include <cmath>
#include "MilitaryUnit.h"

namespace sfGame
{

class Rotate
{
    public:
        Rotate(float omega): omega(omega) {}
        bool rotate(MilitaryUnit &unit, const sf::Vector2f &destination);
    protected:
        float omega;
};

// class PlayerRotate: public Rotate
// {
//     public:
//         PlayerRotate(float omega): Rotate(omega) {}
//         bool rotate(sf::Sprite &sprite, const sf::Vector2f &destination);
// };

}

#endif