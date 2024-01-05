
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

class Movable;
class Rotatable;
class Detect;
class Shell;
class Attack;


class MilitaryUnit
{
    public:
        MilitaryUnit(Side side, sf::Sprite sprite, int HP, int ATK, float attackRange, sf::Time attackInterval);
        virtual ~MilitaryUnit() = default;
        //virtual bool detect(const Units &enemies) = 0;
        sf::FloatRect getBounds() const;
        float getRadius() const;
        sf::Vector2f getPos() const;
        sf::Sprite  getSprite() const;
        sf::Sprite& getSprite();
        int getHP() const;
        // float getDEF() const;
        bool isDead() const;
        virtual Type getType() const = 0;
        Side getSide() const;
        int getATK() const;
        virtual void move() = 0;
        virtual bool detect() = 0;
        virtual bool rotate() = 0;
        virtual bool attack(sf::Time delta) = 0;
        void beingAttacked(int damage);
        virtual void handleInput(sf::RenderWindow &window) = 0;
        virtual void update(sf::Time delta) = 0;
        void render(sf::RenderWindow& window);
    protected:
        Side side;
        sf::Sprite sprite; //贴图
        int HP; //血量
        int ATK;

        
        Movable *moveBehavior;
        sf::Vector2f moveDest;
        Rotatable *rotateBehavior;
        sf::Vector2f rotateDest;
        Detect *detectBehavior;
        Attack *attackBehavior;
        MilitaryUnit *target;
        float attackRange;
        sf::Time attackInterval;

        sf::Time attackClock;
        

};


typedef std::vector<MilitaryUnit*> Units;
typedef std::vector<sf::Vector2f> Route;





}


#endif