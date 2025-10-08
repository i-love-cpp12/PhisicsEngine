#include "collisions.hpp"

Engine2D::Collision Engine2D::getCollisionCircleCircle(const CircleColideData &c1, const CircleColideData &c2)
{
    Collision collision;
    const Vector2D p1 = c1.pos;
    const Vector2D p2 = c2.pos;
                              //Sum of radiuses                   //Distance
    collision.collisonDepth = (c1.radius + c2.radius) - (p1.distance(p2));

    //if radiuses are bigger then distance, isCollision = true
    if(collision.collisonDepth <= 0.0f)
    {
        collision.isCollision = false;
        return collision;
    }

    collision.isCollision = true;
    if(p1 != p2)
        collision.normal = (p1 - p2).getNormalized();
    else
        collision.normal = Vector2D(GetRandomValue(0, 10), GetRandomValue(0, 10)).getNormalized();

    return collision;
}

Engine2D::Collision Engine2D::getCollisionPolygonPolygon(const PolygonColideData &p1, const PolygonColideData &p2)
{
    return Collision();
}

Engine2D::Collision Engine2D::getCollisionCirclePolygon(const CircleColideData &c, const PolygonColideData &p)
{
    return Collision();
}
