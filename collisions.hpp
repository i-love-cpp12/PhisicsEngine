#pragma once

#include"vector2d.hpp"
#include<vector>
#include"math.hpp"
#include<functional>
#include <limits>

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
        std::vector<Vector2D> vertesies;
    };

    MinMax<float> projectVertesies(const std::vector<Vector2D>& vertesies, const Vector2D axe);
    float projectedOverlap(const MinMax<float>& p1, const MinMax<float>& p2);
    Vector2D getCenter(const std::vector<Vector2D>& vertesies);

    Collision getCollisionCircleCircle(const CircleColideData& c1, const CircleColideData& c2);
    Collision getCollisionPolygonPolygon(const PolygonColideData& p1, const PolygonColideData& p2);
    Collision getCollisionCirclePolygon(const CircleColideData& c, const PolygonColideData& p);
}