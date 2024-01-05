#include "Player.h"
#include <iostream>

using namespace sfGame;

Player::Player(Side side, sf::Sprite sprite, int HP, int ATK, float attackRange, sf::Time attackInterval, float FOV):
    MilitaryUnit(side, sprite, HP, ATK, attackRange, attackInterval) 
    {
        // moveDest = sprite.getPosition();
        moveBehavior = new PlayerMove(3);
        rotateBehavior = new Rotatable(1);
        attackBehavior = new Attack(ShellSize::medium, ATK);
        if(!moveBehavior || !rotateBehavior || !attackBehavior)
            std::cout<<"new error!"<<std::endl;
    }

Player::~Player()
{
    delete moveBehavior;
    delete rotateBehavior;
    delete attackBehavior;
}


void Player::handleInput(sf::RenderWindow &window)
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		// {
		// 	direction_ = Direction::Up;
		// 	accelerate_=true;	
		// }
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		// {	
		// 	direction_ = Direction::Down;
		// 	accelerate_=true;	
		// }
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		// {	
		// 	direction_ = Direction::Left;
		// 	accelerate_=true;
		// }	
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		// {
		// 	direction_ = Direction::Right;
		// 	accelerate_=true;
		// }
		// else if(event.type==sf::Event::KeyReleased||event.type==sf::Event::MouseButtonReleased)
		// {
		// 	accelerate_=false;
		// }
		else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            auto relativePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)); 
            // auto offset = window.getView().getCenter() - sf::Vector2f(Game::windowWidth/2, Game::windowHeight/2);
            auto offset = window.getView().getCenter() - sf::Vector2f(640, 480);
            auto absPos = relativePos + offset;
            for(auto unit: Battlefield::getUnits())
            {
                if(unit->getSide() == side) 
                    continue;
                auto x = absPos.x - unit->getPos().x;
                auto y = absPos.y - unit->getPos().y;
                auto distance = sqrt(x*x + y*y);
                if(distance < unit->getRadius())
                {
                    target = unit;
                    rotateDest = unit->getPos();
                    moveDest = getPos(); //别动！
                    return ;
                }
            }

			moveDest = absPos;
            rotateDest = absPos;
            // std::cout<<moveDest.x<<","<<moveDest.y<<std::endl;
		}
	}

}

void Player::update(sf::Time delta)
{
    if(isDead()) return;
    if(!rotate())
    {
        if(!attack(delta))
            move();
    }     
}

Type Player::getType() const
{
    return Type::player;
}



void Player::move()
{
    moveBehavior->move(*this, moveDest);
}

bool Player::rotate()
{
    return rotateBehavior->rotate(*this, rotateDest);
}

void Player::refresh()
{
    std::this_thread::sleep_for(std::chrono::seconds(Parameter::refreshGap));
    sprite.setPosition(sf::Vector2f(800,85));
    HP = Parameter::playerHP;
}

bool Player::attack(sf::Time delta)
{
    
    attackClock += delta;
    // std::cout<<attackClock.asSeconds()<<std::endl;
    // std::cout<<attackInterval.asSeconds()<<std::endl;
    // std::cout<<delta.asSeconds()<<std::endl;

    if(target == NULL) return false;
    if(Battlefield::getDistance(this, target) > attackRange)
    {
        moveDest = target->getPos();
        return false;
    }


    if(attackClock > attackInterval)
    {
        attackClock = sf::Time::Zero;
        attackBehavior->attack(*this, *target);
        target = NULL;
    }

    moveDest = getPos();
    return true;
}
