#include "Rotatable.h"

#include <iostream>

using namespace sfGame;
bool Rotatable::rotate(MilitaryUnit &unit, const sf::Vector2f &destination)
{
    sf::Sprite& sprite = unit.getSprite();
    auto currentPos=sprite.getPosition();
    float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                +(destination.y-currentPos.y)*(destination.y-currentPos.y));//必须先把double转成float
    if(length == 0) return false;
    // auto direction=static_cast<float>(sprite.getTexture()->getSize().x) 
    //                 * sf::Vector2f(destination.x-currentPos.x,destination.y-currentPos.y)/length; //获取鼠标相对蛇头位置的单位矢量
    auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
    int destDirection;
    if(unit.getSide() == Side::Blue)
        destDirection = int(std::atan2(direction.y,direction.x)/3.1415926535*180.0 + 270.0) % 360;
    else   
        destDirection = int(std::atan2(direction.y,direction.x)/3.1415926535*180.0 + 450.0) % 360;
    auto curDirection = sprite.getRotation();
    float twist;
    if((destDirection < curDirection && curDirection - destDirection < 180) ||
        (destDirection >= curDirection && destDirection - curDirection > 180 ))
        twist = - omega;
    else 
        twist = omega;
    // std::cout <<"cur: "<< curDirection << std::endl;
    // std::cout <<"dest: "<< destDirection << std::endl;
    
    if(abs(destDirection - curDirection) > 2 * omega)
    {
        // sprite.setRotation(curDirection + twist);
        // return false;
        sprite.rotate(twist);
        return true;
    }
        
    else return false;
}