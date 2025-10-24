#include<iostream>
#include"raylib.h"
#include"physicsEngine.hpp"
#include"vector2d.hpp"

int main()
{
    using namespace Engine2D;
    
    PhysicsEngine engine(Vector2D{1200.0f, 700.0f}, "phisicsEngine", 60);
    while(!WindowShouldClose())
    {
        engine.takeStep();
        engine.draw();
    }

    return 0;
}