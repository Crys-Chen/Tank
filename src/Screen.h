#ifndef SCREEN
#define SCREEN

#include <SFML/Graphics.hpp>

namespace sfGame
{
class Screen
{
    public:
        virtual ~Screen() = default;
        virtual void handleInput(sf::RenderWindow& window) = 0;
        virtual void update(sf::Time delta) = 0;
        virtual void render(sf::RenderWindow& window, sf::View &view) = 0;

};
}

#endif