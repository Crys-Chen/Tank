#ifndef BACKGROUND
#define BACKGROUND

#include<SFML\Graphics.hpp>
#include"AssetManager.h"
// #include"MenuScreen_2.h"

namespace sfGame
{
class BackGround
{
    public:
        BackGround();
        void setBack();
        void setTimeRecord();
        void updateTimeRecord();
        void draw(sf::RenderWindow &window);

    private:
        sf::Text timeRecord;
        sf::Texture backTexture;
        sf::Sprite back;
        sf::Clock clock;
};
}

#endif