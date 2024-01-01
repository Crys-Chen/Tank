
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


class MilitaryUnit
{
    public:
        MilitaryUnit(Side side, Type type, sf::Sprite sprite, float HP, float FOV, float DEF):
            side(side), type(type), sprite(sprite),HP(HP),FOV(FOV),DEF(DEF){}
        virtual ~MilitaryUnit() = default;
        //virtual bool detect(const Units &enemies) = 0;
        sf::FloatRect getBounds() const;
        float getRadius() const;
        sf::Vector2f getPos() const;
        sf::Sprite  getSprite() const;
        sf::Sprite& getSprite();
        float getHP() const;
        float getDEF() const;
        bool isDead() const;
        Type getType() const;
        Side getSide() const;
        virtual void move() = 0;
        void beingAttacked(float damage);
        virtual void handleInput(sf::RenderWindow &window) = 0;
        virtual void update(sf::Time delta) = 0;
        void render(sf::RenderWindow& window);
    protected:
        Side  side;
        Type type;
        sf::Sprite sprite; //贴图
        float HP; //血量
        float FOV; //视野半径
        float DEF; //防御力
        
        // Detect *detectBehavior;
        // Attack *attackBehavior;
};


typedef std::vector<MilitaryUnit*> Units;
typedef std::vector<sf::Vector2f> Route;





}


#endif