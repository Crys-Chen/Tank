#include "Shell.h"

using namespace sfGame;
extern AssetManager manager;

Shell::Shell(ShellSize size, const MilitaryUnit &attacker, MilitaryUnit *target)
{
    switch (size)
    {
    case ShellSize::large:
        sprite.setTexture(AssetManager::getTexture("./pictures/large.png"));
        sprite.setOrigin(13,13);
        break;
    case ShellSize::medium:
        sprite.setTexture(AssetManager::getTexture("./pictures/medium.png"));
        sprite.setOrigin(10,10);
        break;
    case ShellSize::small:
        sprite.setTexture(AssetManager::getTexture("./pictures/small.png"));
        sprite.setOrigin(16,16);
        break;
    default:
        break;
    }
    sprite.setPosition(attacker.getPos());

    damage = attacker.getATK();
    hit = false;
    this->target = target;
    // std::cout<<"damage: "<<damage<<std::endl;
    
}



bool Shell::attack()
{
    auto currentPos = sprite.getPosition();
    auto destination = target->getPos();
    auto velocity = Parameter::shellVelocity;
    float length=sqrt((destination.x-currentPos.x)*(destination.x-currentPos.x)
                +(destination.y-currentPos.y)*(destination.y-currentPos.y));//必须先把double转成float
    // if(length == 0) return;

    auto direction = sf::Vector2f(destination.x-currentPos.x , destination.y-currentPos.y) / length;
    auto xOffset = direction.x*velocity;
    auto yOffset = direction.y*velocity;
    
    auto distance = currentPos - destination;
    
    if(abs(distance.x) > abs(xOffset))
        currentPos.x += xOffset;
    else 
        currentPos.x = destination.x;
    if(abs(distance.y) > abs(yOffset))
        currentPos.y += yOffset;
    else 
        currentPos.y = destination.y;
    sprite.setPosition(currentPos);

    if(currentPos == destination)
        return true;
    else 
        return false;
}

void Shell::update()
{
    if(hit == true) return;
    if(attack())
    {
        hurt();
        hit = true;
    }
        
}

bool Shell::isOver()
{
    return hit;
}

void Shell::hurt()
{
    target->beingAttacked(damage);

}

void Shell::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

