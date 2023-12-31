#ifndef ROTATABLE
#define ROTATABLE

#include "Game.h"

namespace sfGame
{

class Rotatable
{
    public:
        Rotatable(float omega): omega(omega) {}
        void rotate();
    private:
        float omega;
};

}

#endif