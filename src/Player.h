#ifndef PLAYER
#define PLAYER

#include "MilitaryUnit.h"
#include "Movable.h"
#include "Rotatable.h"

namespace sfGame{

class Player: public MilitaryUnit
{
    public: 
        Player(Side side, sf::Sprite sprite, float HP, float FOV, float DEF);
        ~Player();
        void handleInput(sf::RenderWindow &window);
        void update(sf::Time delta);
        bool rotate();
        void move();
        bool detect() {return false;}
        // bool checkCollision(const Units &units);
        // void render(sf::RenderWindow& window);

    private:
        sf::Vector2f destination;
        Movable *moveBehavior;
        Rotatable *rotateBehavior;
};

}

#endif


