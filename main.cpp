#include<iostream>
#include"raylib.h"
#include"phyisicsEngine.hpp"
#include"vector2d.hpp"

int main()
{
    using namespace Engine2D;

    PhyisicsEngine engine(Vector2D{1200.0f, 700.0f}, "phisicsEngine", 60);
    while(!WindowShouldClose())
    {
        engine.update();
        engine.draw();
    }

    return 0;
}