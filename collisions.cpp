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

Engine2D::Collision Engine2D::getCollisionPolygonPolygon(const PolygonColideData &p1, const PolygonColideData &p2)//is not working well
{
    std::function<bool(const PolygonColideData&, const PolygonColideData&)> isGap = [](const PolygonColideData&p1, const PolygonColideData&p2) -> bool
    {
        for(size_t i = 0; i < p1.vertesies.size(); ++i)
        {
            const Vector2D edge = p1.vertesies[i] - p1.vertesies[(i + 1) % p1.vertesies.size()];
            const Vector2D axe = Vector2D(-edge.y, edge.x).getNormalized();

            std::vector<float> p1Projected;
            std::vector<float> p2Projected;

            p1Projected.reserve(p1.vertesies.size());
            p2Projected.reserve(p2.vertesies.size());

            for(const auto& vertex : p1.vertesies)
            {
                p1Projected.push_back(vertex.getDotProduct(axe));
            }
            for(const auto& vertex : p2.vertesies)
            {
                p2Projected.push_back(vertex.getDotProduct(axe));
            }

            const MinMax<float> p1MinMax = getMinMax(p1Projected);
            const MinMax<float> p2MinMax = getMinMax(p2Projected);
            if(p1MinMax.max < p2MinMax.min || p1MinMax.min > p2MinMax.max) return true;
        }
        return false;
    };
    Collision collison;
    collison.isCollision = !isGap(p1, p2) && !isGap(p2, p1);
    return collison;
}

Engine2D::Collision Engine2D::getCollisionCirclePolygon(const CircleColideData &c, const PolygonColideData &p)
{
    return Collision();
}
