#include "transform.hpp"

Engine2D::Transform::Transform(const Vector2D& rotationCenter, float rotation): rotationCenter(rotationCenter), sin(std::sin(rotation)), cos(std::cos(rotation))
{
}

Engine2D::Vector2D Engine2D::Transform::apply(const Transform &transform, const Vector2D& point)
{

    return Vector2D
        (transform.rotationCenter.x * transform.cos - transform.rotationCenter.y * transform.sin,
        transform.rotationCenter.x * transform.sin - transform.rotationCenter.y * transform.cos)
        + transform.rotationCenter;
}
