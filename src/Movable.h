#ifndef MOVABLE
#define MOVABLE

#include <SFML/Graphics.hpp>
#include "MilitaryUnit.h"
#include "Battlefield.h"

namespace sfGame
{
typedef std::vector<sf::Vector2f> Route;

class Movable
{
    public:
        Movable(float velocity): velocity(velocity) {}
        virtual ~Movable() = default;
        virtual void setRoute(const Route &route) = 0;
        virtual void move(MilitaryUnit &unit, sf::Vector2f &destination) = 0;
    protected:
        float velocity;
};

class PlayerMove: public Movable
{
    public:
        PlayerMove(float velocity): Movable(velocity) {}
        ~PlayerMove() = default;
        void setRoute(const Route &route) {}
        void move(MilitaryUnit &unit, sf::Vector2f &destination);
};

class SoldierMove: public Movable
{
    public:
        SoldierMove(float velocity): Movable(velocity) {}
        ~SoldierMove() = default;
        void setRoute(const Route &route);
        void move(MilitaryUnit &unit, sf::Vector2f &destination);

    private:
        Route route;
        void updateDest(const MilitaryUnit &unit, sf::Vector2f &destination);
    
};

}

#endif