#include<iostream>
#include"raylib.h"
#include"phisicsEngine.hpp"
#include"vector2d.hpp"

int main()
{
    using namespace Engine2D;

    PhisicsEngine engine(Vector2D{1200.0f, 700.0f}, "phisicsEngine", 60);
    while(!WindowShouldClose())
    {
        engine.update();
        engine.draw();
    }

    return 0;
}