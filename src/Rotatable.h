#ifndef ROTATABLE
#define ROTATABLE

#include <SFML/Graphics.hpp>
#include <cmath>

namespace sfGame
{

class Rotatable
{
    public:
        Rotatable(float omega): omega(omega) {}
        bool rotate(sf::Sprite &sprite, const sf::Vector2f &destination);
    private:
        float omega;
};

}

#endif