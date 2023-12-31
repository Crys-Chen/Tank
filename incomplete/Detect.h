#ifndef DETECT
#define DETECT
#include "MilitaryUnit.h"
#include <algorithm>
#include <queue>

namespace sfGame
{
typedef std::vector<MilitaryUnit*> Units;

class Detect
{
    public:
        Detect(sf::Time detectInterval, sf::Vector2f position, float FOV):
            detectInterval(detectInterval), position(position), FOV(FOV){}
        
        void setPos(sf::Vector2f position);
        bool see(sf::Vector2f unit1, sf::Vector2f unit2);
        float getDistance(sf::Vector2f unit1, sf::Vector2f unit2);
        virtual void detect(const Units &enemies) = 0;
        void update(const Units &enemies);
    protected:
        sf::Time detectInterval;
        sf::Vector2f position;
        float FOV;
};

class LockDetect: public Detect
{
    public:
        LockDetect(sf::Time detectInterval, sf::Vector2f position, float FOV): 
            Detect(detectInterval,position,FOV), target(NULL){}
        void detect(const Units &enemies);
        // std::queue<MilitaryUnit*> enemyQueue;
        MilitaryUnit* target;

};

class MinDetect: public Detect
{
    public:
        MinDetect(sf::Time detectInterval, sf::Vector2f position, float FOV): 
            Detect(detectInterval,position,FOV), target(NULL){}
        void detect(const Units &enemies);
        // std::queue<MilitaryUnit*> enemyQueue;
        MilitaryUnit* target;

        struct Object{
            MilitaryUnit *target;
            float        distance;

            Object(MilitaryUnit *target, float distance): target(target), distance(distance) {}
        };

        struct cmp{
            bool operator()(Object a, Object b){
                return a.distance > b.distance; 
            }
        };

};
}

#endif
