#include "transform.hpp"

Engine2D::Transform::Transform(const Vector2D& rotationCenter, float rotation): rotationCenter(rotationCenter), sin(std::sin(rotation * (3.14159265f / 180.0f))), cos(std::cos(rotation * (3.14159265f / 180.0f)))
{
}

Engine2D::Vector2D Engine2D::Transform::apply(const Transform &transform, const Vector2D& localPoint)
{
    float x_rot = localPoint.x * transform.cos - localPoint.y * transform.sin;
    float y_rot = localPoint.x * transform.sin + localPoint.y * transform.cos;

    return Vector2D(x_rot + transform.rotationCenter.x, y_rot + transform.rotationCenter.y);
}
