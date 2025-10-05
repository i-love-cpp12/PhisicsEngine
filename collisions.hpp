#pragma once

#include"vector2d.hpp"

namespace Engine2D
{
    struct Collision
    {
        bool isCollision;
        Vector2D normal;
        float collisonDepth;
    };

    struct CircleColideData
    {
        Vector2D pos;
        float radius;
    };

    Collision getCollisionCircleCircle(const CircleColideData& c1, const CircleColideData& c2);
}