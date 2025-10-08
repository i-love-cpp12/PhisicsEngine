#include "body.hpp"

Engine2D::Body::Body(const Vector2D &position, float weight, BodyType type, bool isStatic, float rotation, float dencity, float restitution):
    position(position),
    linearVelocity({0.0f, 0.0f}),
    rotation(rotation),
    angularVelocity(0.0f),
    weight(weight),
    dencity(dencity),
    restitution(restitution),
    isStatic(isStatic),
    type(type),
    movementNotApplied(true)
{
}

void Engine2D::Body::moveTo(const Vector2D& newPos)
{
    position = newPos;
    movementNotApplied = true;
}

void Engine2D::Body::moveBy(const Vector2D &amount)
{
    position = position + amount;
    movementNotApplied = true;
}

void Engine2D::Body::rotate(float amount)
{
    rotation += amount;
    movementNotApplied = true;
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
        {
            CircleBody otherCircle = static_cast<const CircleBody&>(body);
            return getCollisionCircleCircle({position, radius}, {otherCircle.getPosition(), otherCircle.getRadius()});
        }
        break;

        case rectangle:
        {
            return Collision();
        }
        break;

        case polygon:
        {
            return Collision();
        }
        break;
    };
    return Collision();
}

Engine2D::RectangleBody::RectangleBody(const Vector2D &position, float width, float height, float weight, bool isStatic, float dencity, float restitution):
    Engine2D::Body::Body(position, weight, rectangle, isStatic, 0.0f, dencity, restitution), width(width), height(height),
    localVertecies({
        Vector2D(-width / 2, -height / 2),
        Vector2D(width / 2, -height / 2),
        Vector2D(width / 2, height / 2),
        Vector2D(-width / 2, height / 2)
    })
{
}

void Engine2D::RectangleBody::draw(Color color, float strokeSize) const
{
    Rectangle rect = {position.x, position.y, width, height};
    DrawRectanglePro(rect, {width / 2.0f, height / 2.0f}, rotation, color);
    DrawRectangleLinesEx({rect.x, rect.y, rect.width - strokeSize, rect.height - strokeSize}, strokeSize, BLACK);
}

Engine2D::Collision Engine2D::RectangleBody::getCollision(const Body &body) const
{
    switch(body.getType())
    {
        case circle:
        {
        }
        break;

        case rectangle:
        {
            return Collision();
        }
        break;

        case polygon:
        {
            return Collision();
        }
        break;
    };
    return Collision();
}

std::array<Engine2D::Vector2D, 4>& Engine2D::RectangleBody::getVertices()
{
    if(movementNotApplied)
    {
        applyVertecies();
        movementNotApplied = false;
    }
    return appliedVertecies;
}

void Engine2D::RectangleBody::applyVertecies()
{
    for(size_t i = 0; i < localVertecies.size(); ++i)
    {
        appliedVertecies[i] = Transform::apply(Transform(position, rotation), localVertecies[i]);
    }
}
