#ifndef MOVABLE
#define MOVABLE

#include <SFML/Graphics.hpp>
#include "MilitaryUnit.h"
#include "Battlefield.h"

namespace sfGame
{

class Movable
{
    public:
        Movable(float velocity): velocity(velocity) {}
        virtual ~Movable() = default;
        // bool checkCollision(const MilitaryUnit &unit, const Units &units, sf::Vector2f &collisionObj);
        virtual void move(MilitaryUnit &unit, sf::Vector2f &destination) = 0;
    protected:
        float velocity;
        // bool checkUnitCollison(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
        // bool checkObstacleCollison(const sf::Sprite &sprite1, sf::Vector2f &collisionObj);
};

class PlayerMove: public Movable
{
    public:
        PlayerMove(float velocity): Movable(velocity) {}
        ~PlayerMove() = default;
        void move(MilitaryUnit &unit, sf::Vector2f &destination);
};

}

#endif