#include "collisions.hpp"
#include"body.hpp"

Engine2D::Collision Engine2D::getCollisionCircleCircle(const CircleBody &c1, const CircleBody &c2)
{
    Collision collision;
    const Vector2D p1 = c1.getPosition();
    const Vector2D p2 = c2.getPosition();
                              //Sum of radiuses                   //Distance
    collision.collisonDepth = (c1.getRadius() + c2.getRadius()) - (p1.distance(p2));

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