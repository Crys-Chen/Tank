#include "MilitaryUnit.h"

using namespace sfGame;

sf::FloatRect MilitaryUnit::getBounds() const
{
    return sprite.getGlobalBounds();
}

float MilitaryUnit::getRadius() const
{
    return sprite.getGlobalBounds().height/2;
}

sf::Vector2f MilitaryUnit::getPos() const
{
    return sprite.getPosition();
}

void MilitaryUnit::beingAttacked(float damage)
{
    if(HP - damage > 0)
        HP -= damage;
    else HP = 0;
}

float MilitaryUnit::getHP() const
{
    return HP;
}

float MilitaryUnit::getDEF() const
{
    return DEF;
}

bool MilitaryUnit::isDead() const
{
    return HP<=0;
}

bool MilitaryUnit::isPlayer() const
{
    return isPlayer_;
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
}

// bool MilitaryUnit::see(sf::Vector2f enemyPos)
// {
//     auto distanceX = enemyPos.x - getPos().x;
//     auto distanceY = enemyPos.y - getPos().y;
//     return sqrt(distanceX * distanceX + distanceY * distanceY) < FOV;
// }

// bool MilitaryUnit::detect(const Units &enemies)
// {
// 	for (auto it = enemies.begin(); it != enemies.end(); ++it)
// 	{
// 		if (see(it->getPos())) //检测到了敌人
// 			toRemove = it; //吃到了it这个果子
// 	}

// 	if (toRemove != fruits.end()) //吃到果子了
// 	{
// 		pickupSound_.play();
// 		auto score=toRemove->score();
// 		while(score--) grow(); //按分数生长
// 		fruits.erase(toRemove); //删掉toRemove这个果子
// 	}
// }


