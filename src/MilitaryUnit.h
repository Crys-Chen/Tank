
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
    soldier
};

class Movable;
class Rotatable;
class Detect;
class Shell;
class Attack;


class MilitaryUnit
{
    public:
        MilitaryUnit(Side side, sf::Sprite sprite, int HP, int ATK);
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
        void beingAttacked(float damage);
        virtual void handleInput(sf::RenderWindow &window) = 0;
        virtual void update(sf::Time delta) = 0;
        void render(sf::RenderWindow& window);
    protected:
        Side side;
        sf::Sprite sprite; //贴图
        int HP; //血量
        int ATK;

        sf::Vector2f destination;
        Movable *moveBehavior;
        Rotatable *rotateBehavior;
        Detect *detectBehavior;
        Attack *attack;
        

};


typedef std::vector<MilitaryUnit*> Units;
typedef std::vector<sf::Vector2f> Route;





}


#endif