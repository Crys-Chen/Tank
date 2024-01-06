#ifndef PLAYER
#define PLAYER
#include <thread>
#include <ctime>
#include <chrono>
#include "MilitaryUnit.h"
#include "Move.h"
#include "AssetManager.h"
#include "Rotatable.h"
#include "Attack.h"

namespace sfGame{

class Player: public MilitaryUnit
{
    public: 
        Player(Side side, sf::Sprite sprite, int HP, int ATK, float attackRange, sf::Time attackInterval, float velocity, float omega);
        ~Player();
        void handleInput(sf::RenderWindow &window);
        void update(sf::Time delta);
        void render(sf::RenderWindow &window);
        Type getType() const;
        bool rotate();
        bool attack(sf::Time delta);
        void move();
        void refresh();
        bool detect() {return false;}
        // bool checkCollision(const Units &units);
        // void render(sf::RenderWindow& window);

    private:
        sf::CircleShape lockCircle;
        
};

}

#endif


