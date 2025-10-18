#include "collisions.hpp"

Engine2D::MinMax<float> Engine2D::projectVertesies(const std::vector<Vector2D> &vertesies, const Vector2D axe)
{
    MinMax<float> minmax;
    minmax.max = minmax.min = vertesies[0].getDotProduct(axe);

    for(size_t i = 1; i < vertesies.size(); ++i)
    {
        float projected = vertesies[i].getDotProduct(axe);
        if(projected > minmax.max) minmax.max = projected;
        if(projected < minmax.min) minmax.min = projected;
    }
    return minmax;
}

float Engine2D::projectedOverlap(const MinMax<float> &p1, const MinMax<float> &p2)
{
    double left = std::max(p1.min, p2.min);
    double right = std::min(p1.max, p2.max);
    return right - left;
}

Engine2D::Vector2D Engine2D::getCenter(const std::vector<Vector2D> &vertesies)
{
    Vector2D sum = Vector2D::ZERO();

    for(const auto& v : vertesies)
    {
        sum = sum + v;
    }
    return sum * (1.0f / vertesies.size());
}

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
    if (p1.vertesies.size() < 3 || p2.vertesies.size() < 3) return Collision{false, Vector2D::ZERO(), 0.0f};

    Collision collision;
    collision.isCollision = true;
    collision.collisonDepth = std::numeric_limits<float>().infinity();

    std::function<void(const PolygonColideData&, const PolygonColideData&)> testEdges = [&collision](const PolygonColideData&a, const PolygonColideData&b) -> void
    {
        for(size_t i = 0; i < a.vertesies.size(); ++i)
        {
            const Vector2D edge = a.vertesies[i] - a.vertesies[(i + 1) % a.vertesies.size()];
            const Vector2D axe = edge.perp().getNormalized();

            float overlap = projectedOverlap(projectVertesies(a.vertesies, axe), projectVertesies(b.vertesies, axe));

            if(overlap < 0.0f)
            {
                collision.isCollision = false;
                return;
            }
            else if(overlap < collision.collisonDepth)
            {
                collision.collisonDepth = overlap;
                collision.normal = axe;
            }
        }
    };
    
    testEdges(p1, p2);
    if(!collision.isCollision) return collision;

    testEdges(p2, p1);
    if(!collision.isCollision) return collision;

    Vector2D distance = getCenter(p1.vertesies) - getCenter(p2.vertesies);

    float direction = collision.normal.getDotProduct(distance);
    
    if(direction < 0.0f) collision.normal = -collision.normal;

    return collision;
}

Engine2D::Collision Engine2D::getCollisionCirclePolygon(const CircleColideData &c, const PolygonColideData &p)
{
    return Collision();
}
