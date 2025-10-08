#pragma once

#include"vector2d.hpp"
#include<vector>

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
    struct PolygonColideData
    {
        Vector2D pos;
        std::vector<Vector2D> vertexes;
    };

    Collision getCollisionCircleCircle(const CircleColideData& c1, const CircleColideData& c2);
}