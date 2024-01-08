#include "Player.h"
#include <iostream>

using namespace sfGame;
extern AssetManager manager;

Player::Player(Side side, sf::Sprite sprite, int HP, int ATK, float attackRange, sf::Time attackInterval, float velocity, float omega):
    MilitaryUnit(side, sprite, HP), lockCircle(30)
    {
        // moveDest = sprite.getPosition();
        moveBehavior = new PlayerMove(velocity);
        rotateBehavior = new Rotate(omega);
        attackBehavior = new Attack(ShellSize::medium, ATK, attackRange, attackInterval);
        lockCircle.setOrigin(15,15);
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
        auto relativePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)); 
            // auto offset = window.getView().getCenter() - sf::Vector2f(Game::windowWidth/2, Game::windowHeight/2);
        auto offset = window.getView().getCenter() - sf::Vector2f(640, 480);
        auto absPos = relativePos + offset;
        MilitaryUnit* tempTarget = NULL;
        lockCircle.setTexture(NULL);

        for(auto unit: Battlefield::getUnits())
        {
            if(unit->getSide() == side || unit->isDead()) 
                continue;
            // if(unit->isDead()) continue;
            auto x = absPos.x - unit->getPos().x;
            auto y = absPos.y - unit->getPos().y;
            auto distance = sqrt(x*x + y*y);
            if(distance < unit->getRadius() * 1.5)
            {
                lockCircle.setPosition(absPos);
                lockCircle.setTexture(&(AssetManager::getTexture("./pictures/lock2.png")));
                tempTarget = unit;
                break;
            }
        }


		if (event.type == sf::Event::Closed) 
            window.close();
		else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            if(tempTarget != NULL)
            {
                target = tempTarget;
                rotateDest = target->getPos();
                moveDest = getPos(); //别动！
            }
            else
            {
                target = NULL;
                moveDest = absPos;
                rotateDest = absPos;
            }

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

void Player::render(sf::RenderWindow& window)
{
    window.draw(sprite);
    if(lockCircle.getTexture() != NULL)
        window.draw(lockCircle);
    HPbar.setPosition(getPos()+Parameter::HPbarDelta);
    HPbar.setSize(sf::Vector2f(HP*(Parameter::HPbarWidthCoff),Parameter::HPbarHeight));
    window.draw(HPbar);
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
    rotateDest = getPos() + sf::Vector2f(0,20);
    rotate();
    target = NULL;
    std::this_thread::sleep_for(std::chrono::seconds(Parameter::refreshGap));
    sprite.setPosition(sf::Vector2f(800,85));
    moveDest = getPos();
    HP = Parameter::playerHP;
}

bool Player::attack(sf::Time delta)
{
    return attackBehavior->attack(*this, delta);
}
