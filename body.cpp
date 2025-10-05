#include "body.hpp"
#include"collisions.hpp"

Engine2D::Body::Body(const Vector2D &position, float weight, BodyType type, bool isStatic, float rotation, float dencity, float restitution):
    position(position),
    linearVelocity({0.0f, 0.0f}),
    rotation(rotation),
    angularVelocity(0.0f),
    weight(weight),
    dencity(dencity),
    restitution(restitution),
    isStatic(isStatic),
    type(type)
{
}

void Engine2D::Body::moveTo(const Vector2D& newPos)
{
    position = newPos;
}

Engine2D::CircleBody::CircleBody(const Vector2D &position, float radius, float weight, bool isStatic, float dencity, float restitution):
    Engine2D::Body::Body(position, weight, circle, isStatic, 0.0f, dencity, restitution), radius(radius)
{
}

void Engine2D::CircleBody::draw(Color color, float strokeSize) const
{
    const float QUALITY = 1.0f;
    DrawCircleV(position.toRaylibVector(), radius, color);
    DrawRing(position.toRaylibVector(), radius - strokeSize, radius, 0.0f, 360.0f, radius * QUALITY, BLACK);
}

Engine2D::Collision Engine2D::CircleBody::getCollision(const Body &body) const
{
    switch(body.getType())
    {
        case circle:
            return getCollisionCircleCircle(*this, static_cast<const CircleBody&>(body));
        break;

        case rectangle:
            return Collision();
        break;

        case polygon:
            return Collision();
        break;
    };
    return Collision();
}
