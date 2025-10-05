#include "transform.hpp"

Engine2D::Transform::Transform(const Vector2D& rotationCenter, float rotation): rotationCenter(rotationCenter), sin(std::sin(rotation)), cos(std::cos(rotation))
{
}

Engine2D::Vector2D Engine2D::Transform::apply(const Transform &transform, const Vector2D& point)
{
    const Vector2D distance = point - transform.rotationCenter;

    const Vector2D rotation = Vector2D(distance.x * transform.cos - distance.y * transform.sin,
                                        distance.x * transform.sin - distance.y * transform.cos);
    return transform.rotationCenter + rotation;
}
