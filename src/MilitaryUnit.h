
#ifndef UNIT
#define UNIT
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <memory>
#include <cstdlib>



namespace sfGame
{


enum Side
{
    Red,Blue
};

enum Type
{
    player,
    tower,
    soldier,
    nexus
};

class Move;
class Rotatable;
class Detect;
class Shell;
class Attack;


class MilitaryUnit
{
    public:
        MilitaryUnit(Side side, sf::Sprite sprite, int HP);
        virtual ~MilitaryUnit() = default;
        // sf::FloatRect getBounds() const;
        
        sf::Vector2f getPos() const;
        sf::Sprite  getSprite() const;
        sf::Sprite& getSprite();
        Side getSide() const;

        float getRadius() const;
        int getHP() const;
        bool isDead() const;

        void beingAttacked(int damage);
        
        virtual Type getType() const = 0;
        virtual void move() = 0;
        virtual bool detect() = 0;
        virtual bool rotate() = 0;
        virtual bool attack(sf::Time delta) = 0;
        
        virtual void handleInput(sf::RenderWindow &window) = 0;
        virtual void update(sf::Time delta) = 0;
        void render(sf::RenderWindow& window);

        friend class Attack;
    protected:
        Side side;
        sf::Sprite sprite; //贴图
        int HP; //血量
        // int ATK;

        
        Move *moveBehavior;
        sf::Vector2f moveDest;
        Rotatable *rotateBehavior;
        sf::Vector2f rotateDest;
        Detect *detectBehavior;
        Attack *attackBehavior;
        MilitaryUnit *target;
        // float attackRange;
        // sf::Time attackInterval;

        // sf::Time attackClock;
        

};


typedef std::vector<MilitaryUnit*> Units;
typedef std::vector<sf::Vector2f> Route;





}


#endif