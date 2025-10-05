#pragma once

#include"vector2d.hpp"

namespace Engine2D
{
    class CircleBody;
    struct Collision
    {
        bool isCollision;
        Vector2D normal;
        float collisonDepth;
    };

    Collision getCollisionCircleCircle(const CircleBody& c1, const CircleBody& c2);
}