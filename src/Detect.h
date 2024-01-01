#ifndef DETECT
#define DETECT
#include "MilitaryUnit.h"
#include "Battlefield.h"
#include <algorithm>
#include <queue>
#include <random>
#include <time.h>

namespace sfGame
{

class Detect
{
    public:
        Detect(float FOV): FOV(FOV) {}
        virtual ~Detect() = default;
        virtual bool detect(MilitaryUnit *self, MilitaryUnit *&target) = 0;
    
    protected:
        float FOV;

};

class LockDetect: public Detect
{
    public:
        LockDetect(float FOV);
        ~LockDetect() = default;
        bool detect(MilitaryUnit *self, MilitaryUnit *&target);

    private:
        std::default_random_engine random;

};

class MinDetect: public Detect
{
    public:
        MinDetect(float FOV):Detect(FOV) {}
        ~MinDetect() = default;
        bool detect(MilitaryUnit *self, MilitaryUnit *&target);

        struct Enemy{
            MilitaryUnit *target;
            float        distance;

            Enemy(MilitaryUnit *target, float distance): target(target), distance(distance) {}
        };

        struct cmp{
            bool operator()(Enemy a, Enemy b){
                return a.distance > b.distance; 
            }
        };

};
}

#endif
