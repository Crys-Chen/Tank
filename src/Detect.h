#ifndef DETECT
#define DETECT
#include "MilitaryUnit.h"
#include "Battlefield.h"
#include <algorithm>
#include <queue>

namespace sfGame
{

class Detect
{
    public:
        Detect() = default;
        virtual ~Detect() = default;
        virtual bool detect(const Units &enemies, MilitaryUnit &object) = 0;

};

class LockDetect: public Detect
{
    public:
        LockDetect():Detect() {}
        bool detect(const Units &enemies, MilitaryUnit &object);

};

// class MinDetect: public Detect
// {
//     public:
//         MinDetect(sf::Time detectInterval, sf::Vector2f position, float FOV): 
//             Detect(detectInterval,position,FOV), target(NULL){}
//         void detect(const Units &enemies);
//         // std::queue<MilitaryUnit*> enemyQueue;
//         MilitaryUnit* target;

//         struct Object{
//             MilitaryUnit *target;
//             float        distance;

//             Object(MilitaryUnit *target, float distance): target(target), distance(distance) {}
//         };

//         struct cmp{
//             bool operator()(Object a, Object b){
//                 return a.distance > b.distance; 
//             }
//         };

// };
}

#endif
