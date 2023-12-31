#include "Movable.h"
// #include "Game.h"

#include <cmath>
#include <iostream>

using namespace sfGame;

extern Battlefield battlefield;

// bool Movable::checkUnitCollison(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
// {
//     if(sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()))
//     {
//         std::cout<<sprite1.getGlobalBounds().left<<","<<sprite1.getGlobalBounds().top<<","<<sprite1.getGlobalBounds().width<<","<<sprite1.getGlobalBounds().height<<std::endl;
//         std::cout<<sprite2.getGlobalBounds().left<<","<<sprite2.getGlobalBounds().top<<","<<sprite2.getGlobalBounds().width<<","<<sprite2.getGlobalBounds().height<<std::endl;
//     }
        
//     return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
// }

// bool Movable::checkObstacleCollison(const sf::Sprite &sprite, sf::Vector2f &collisionObj)
// {
//     sf::Rect<float> obstacle[8];
//     obstacle[0].left = 353;
//     obstacle[0].top = 308;
//     obstacle[0].width = 100;
//     obstacle[0].height = 262;

//     obstacle[1].left = 249;
//     obstacle[1].top = 462;
//     obstacle[1].width = 130;
//     obstacle[1].height = 100;

//     obstacle[2].left = 819;
//     obstacle[2].top = 316;
//     obstacle[2].width = 100;
//     obstacle[2].height = 262;

//     obstacle[3].left = 934;
//     obstacle[3].top = 478;
//     obstacle[3].width = 90;
//     obstacle[3].height = 100;

//     obstacle[4].left = 254;
//     obstacle[4].top = 2301;
//     obstacle[4].width = 202;
//     obstacle[4].height = 100;

//     obstacle[5].left = 371;
//     obstacle[5].top = 2428;
//     obstacle[5].width = 100;
//     obstacle[5].height = 100;


//     obstacle[6].left = 828;
//     obstacle[6].top = 2305;
//     obstacle[6].width = 100;
//     obstacle[6].height = 262;


    
//     obstacle[7].left = 924;
//     obstacle[7].top = 2310;
//     obstacle[7].width = 100;
//     obstacle[7].height = 110;



//     for(int i = 0; i < 8; i++)
//     {
//         if(sprite.getGlobalBounds().intersects(obstacle[i]))
//         {
//             collisionObj = sf::Vector2f(obstacle[i].left + obstacle[i].width/2, obstacle[i].top + obstacle[i].height/2);
//             return true;
//         }
            
//     }
//     return false;
     
// }

// bool Movable::checkCollision(const MilitaryUnit &unit, const Units &units, sf::Vector2f &collisionObj)
// {
//     if(checkObstacleCollison(unit.getSprite(), collisionObj)) 
//     {
//         std::cout<<"zhuang!"<<std::endl;
//         return true;
//     }
        
//     for(auto i : units)
//     {
//         if(i == &unit)
//             continue;
//         if(checkUnitCollison(unit.getSprite(), i->getSprite()))
//         {
//             std::cout<<"zhuang!"<<std::endl;
//             collisionObj = i->getSprite().getPosition();
//             return true;
//         }
//     }
    
//     return false;
// }

void PlayerMove::move(MilitaryUnit &unit, sf::Vector2f &destination)
{
    sf::Sprite& sprite = unit.getSprite();
    auto currentPos=sprite.getPosition();
    // std::cout<<"move!"<<std::endl;
    if(Battlefield::checkCollision(&unit, destination))
    {
        float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                    +(destination.y-currentPos.y)*(destination.y-currentPos.y));//必须先把double转成float
        if(length == 0) return;
        auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
        auto xOffset = direction.x*velocity;
        auto yOffset = direction.y*velocity;
        currentPos.x -= xOffset;
        currentPos.y -= yOffset;
        sprite.setPosition(currentPos);
        destination = currentPos; //退完就别动了
        return;
    }

   
    float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                +(destination.y-currentPos.y)*(destination.y-currentPos.y));//必须先把double转成float
    if(length == 0) return;
    // auto direction=static_cast<float>(sprite.getTexture()->getSize().x) 
    //                 * sf::Vector2f(destination.x-currentPos.x,destination.y-currentPos.y)/length; //获取鼠标相对蛇头位置的单位矢量
    auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
    auto xOffset = direction.x*velocity;
    auto yOffset = direction.y*velocity;
    
    auto distance = currentPos - destination;
    // std::cout<<xOffset<<","<<yOffset<<std::endl;
    if(abs(distance.x) > abs(xOffset))
        currentPos.x += xOffset;
    if(abs(distance.y) > abs(yOffset))
        currentPos.y += yOffset;
    sprite.setPosition(currentPos);
    // sprite.setRotation(std::atan2(direction.y,direction.x)/3.1415926535*180.0+90.0);

	// sprite.setDirection(sf::Vector2f(xOffset,yOffset));
}
