#include "vector2d.hpp"
#include <cmath>

using namespace Engine2D;
Vector2D::Vector2D(float x, float y): x(x), y(y)
{}
Vector2D::Vector2D(): x(0.0f), y(0.0f)
{
}
Vector2D Vector2D::ZERO()
{
    return Vector2D(0.0f, 0.0f);
}

Vector2 Vector2D::toRaylibVector() const
{
    return Vector2{x, y};
}

float Engine2D::Vector2D::getLength() const
{
    return std::hypot(x, y);
}

bool Engine2D::Vector2D::isEqual(const Vector2D &other) const
{
    return x == other.x && y == other.y;
}

bool Engine2D::Vector2D::operator==(const Vector2D &other) const
{
    return isEqual(other);
}

bool Engine2D::Vector2D::operator!=(const Vector2D &other) const
{
    return !isEqual(other);
}

Vector2D Engine2D::Vector2D::add(const Vector2D &other) const
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Engine2D::Vector2D::operator+(const Vector2D &other) const
{
    return add(other);
}

Vector2D Engine2D::Vector2D::subtract(const Vector2D &other) const
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Engine2D::Vector2D::operator-(const Vector2D &other) const
{
    return subtract(other);
}

Vector2D Engine2D::Vector2D::toggleSign() const
{
    return Vector2D(-x, -y);
}

Vector2D Engine2D::Vector2D::operator-() const
{
    return toggleSign();
}

Vector2D Engine2D::Vector2D::multiply(const Vector2D &other) const
{
    return Vector2D(x * other.x, y * other.y);
}

Vector2D Engine2D::Vector2D::operator*(const Vector2D &other) const
{
    return multiply(other);
}

Vector2D Engine2D::Vector2D::multiply(float scalar) const
{
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Engine2D::Vector2D::operator*(float scalar) const
{
    return multiply(scalar);
}

float Engine2D::Vector2D::distance(const Vector2D &other) const
{
    const Vector2D diff = *this - other;
    return diff.getLength();
}

Vector2D Engine2D::Vector2D::getNormalized() const
{
    const float lenght = getLength();
    if(lenght == 0) return *this;
    return Vector2D(x / lenght, y / lenght);
}

float Engine2D::Vector2D::getDotProduct(const Vector2D &other) const
{
    return x * other.x + y * other.y;
}

Vector2D Engine2D::Vector2D::perp() const
{
    return Vector2D(-y, x);
}

std::ostream &Engine2D::Vector2D::print(std::ostream &stream) const
{
    stream<<"(x: "<<x<<" y: "<<y<<')';
    return stream;
}
