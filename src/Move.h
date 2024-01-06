#ifndef MOVABLE
#define MOVABLE

#include <SFML/Graphics.hpp>
#include "MilitaryUnit.h"
#include "Battlefield.h"

namespace sfGame
{
typedef std::vector<sf::Vector2f> Route;

class Move
{
    public:
        Move(float velocity): velocity(velocity) {}
        virtual ~Move() = default;
        virtual void setRoute(const Route &route) = 0;
        virtual void move(MilitaryUnit &unit, sf::Vector2f &destination) = 0;
    protected:
        float velocity;
};

class PlayerMove: public Move
{
    public:
        PlayerMove(float velocity): Move(velocity) {}
        ~PlayerMove() = default;
        void setRoute(const Route &route) {}
        void move(MilitaryUnit &unit, sf::Vector2f &destination);
};

class SoldierMove: public Move
{
    public:
        SoldierMove(float velocity): Move(velocity) {}
        ~SoldierMove() = default;
        void setRoute(const Route &route);
        void move(MilitaryUnit &unit, sf::Vector2f &destination);

    private:
        Route route;
        void updateDest(const MilitaryUnit &unit, sf::Vector2f &destination);
    
};

}

#endif