#include "MilitaryUnit.h"
#include <iostream>

using namespace sfGame;

MilitaryUnit::MilitaryUnit(Side side, sf::Sprite sprite, int HP):
    side(side), sprite(sprite), HP(HP), HPbar(sf::Vector2f(HP*(Parameter::HPbarWidthCoff),Parameter::HPbarHeight))
{
    moveBehavior = NULL;
    rotateBehavior = NULL;
    detectBehavior = NULL;
    // shell = NULL;
    target = NULL;
    attackBehavior = NULL;
    rotateDest = moveDest = getPos();
     
    HPbar.setFillColor(sf::Color::Green);
    HPbar.setOrigin(HP*(Parameter::HPbarWidthCoff) / 2, Parameter::HPbarHeight/2);
    HPbar.setPosition(getPos()+Parameter::HPbarDelta);
}


// sf::FloatRect MilitaryUnit::getBounds() const
// {
//     return sprite.getGlobalBounds();
// }

float MilitaryUnit::getRadius() const
{
    return sprite.getGlobalBounds().height/2;
}

sf::Vector2f MilitaryUnit::getPos() const
{
    return sprite.getPosition();
}

void MilitaryUnit::beingAttacked(int damage)
{
    if(HP - damage > 0)
        HP -= damage;
    else HP = 0;
}

int MilitaryUnit::getHP() const
{
    return HP;
}

MilitaryUnit* MilitaryUnit::getTarget() const
{
    return target;
}


bool MilitaryUnit::isDead() const
{
    return HP<=0;
}

Side MilitaryUnit::getSide() const
{
    return side;
}

sf::Sprite MilitaryUnit::getSprite() const
{
    return sprite;
}

sf::Sprite& MilitaryUnit::getSprite()
{
    return sprite;
}


void MilitaryUnit::render(sf::RenderWindow& window)
{
    window.draw(sprite);
    HPbar.setPosition(getPos()+Parameter::HPbarDelta);
    HPbar.setSize(sf::Vector2f(HP*(Parameter::HPbarWidthCoff),Parameter::HPbarHeight));
    window.draw(HPbar);
}


