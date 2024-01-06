#include"BackGround.h"
#include"Game.h"
#include<iostream>
#include"GameScreen.h"


using namespace sfGame;
extern AssetManager manager;


BackGround::BackGround()
{
    setBack();
    setTimeRecord();
    back.setScale(2.35,3.30);
}

void BackGround::setBack()
{
    backTexture=AssetManager::getTexture("./pictures/backGround.png");
    back.setTexture(backTexture);
    back.setPosition(0.0f,0.0f);
}



void BackGround::setTimeRecord()
{
    int elapsed_time= clock.getElapsedTime().asSeconds();

    timeRecord.setFont(AssetManager::getFont("Fonts/game.ttf"));
    timeRecord.setString("Time:"+std::to_string(elapsed_time)+"s");
    timeRecord.setFillColor(sf::Color(135,206,235));
    timeRecord.setCharacterSize(20);
    timeRecord.setStyle(sf::Text::Bold); 
    auto time_pos=timeRecord.getLocalBounds();
    timeRecord.setOrigin(time_pos.left,time_pos.top); 
    timeRecord.setPosition(10.0f,10.0f);
}

void BackGround::updateTimeRecord()
{   
    int elapsed_time= clock.getElapsedTime().asSeconds();
    timeRecord.setString("Time:"+std::to_string(elapsed_time)+"s");
}

void BackGround::draw(sf::RenderWindow &window)
{
    updateTimeRecord();
    window.draw(back);
    // window.draw(cell_);
    window.draw(timeRecord);//必须最后绘制，不然会被背景布盖住！！

}