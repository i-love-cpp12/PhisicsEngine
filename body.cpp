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

void Engine2D::Body::rotateTo(float newRotation)
{
    rotation = newRotation;
    movementNotApplied = true;
}

void Engine2D::Body::rotateBy(float amount)
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
            const CircleBody& otherCircle = static_cast<const CircleBody&>(body);
            return getCollisionCircleCircle({position, radius}, {otherCircle.getPosition(), otherCircle.getRadius()});
        }
        break;

        case polygon:
        {
            const PolygonBody& otherPolygon = static_cast<const PolygonBody&>(body);
            return getCollisionCirclePolygon({position, radius}, {otherPolygon.getPosition(), otherPolygon.getVertesies()});
        }
        break;
    };
    throw new std::runtime_error("not valid body");
}

Engine2D::PolygonBody::PolygonBody(const Vector2D &position, float width, float height, float weight, bool isStatic, float dencity, float restitution):
    Engine2D::Body::Body(position, weight, polygon, isStatic, 0.0f, dencity, restitution),
    localVertecies({
        Vector2D(-width / 2, -height / 2),
        Vector2D(width / 2, -height / 2),
        Vector2D(width / 2, height / 2),
        Vector2D(-width / 2, height / 2)
    })
{
}

Engine2D::PolygonBody::PolygonBody(const Vector2D &position, std::vector<Vector2D> localVertecies, float weight, bool isStatic, float dencity, float restitution):
    Engine2D::Body::Body(position, weight, polygon, isStatic, 0.0f, dencity, restitution),
    localVertecies(localVertecies)
{
}

void Engine2D::PolygonBody::draw(Color color, float strokeSize) const
{
    // Rectangle rect = {position.x, position.y, width, height};
    // DrawRectanglePro(rect, {width / 2.0f, height / 2.0f}, rotation, color);
    // DrawRectangleLinesEx({rect.x, rect.y, rect.width - strokeSize, rect.height - strokeSize}, strokeSize, BLACK);
    // DraW
    std::vector<Vector2D> vertesies = getVertesies();
    for(size_t i = 1; i < vertesies.size(); ++i)
    {
        DrawLineV(vertesies[i - 1].toRaylibVector(), vertesies[i].toRaylibVector(), BLACK);
    }
}

Engine2D::Collision Engine2D::PolygonBody::getCollision(const Body &body) const
{
    switch(body.getType())
    {
        case circle:
        {
            const CircleBody& otherCircle = static_cast<const CircleBody&>(body);
            return getCollisionCirclePolygon({otherCircle.getPosition(), otherCircle.getRadius()}, {position, getVertesies()});
        }
        break;

        case polygon:
        {
            const PolygonBody& otherPolygon = static_cast<const PolygonBody&>(body);
            return getCollisionPolygonPolygon({position, getVertesies()}, {otherPolygon.position, otherPolygon.getVertesies()});
        }
        break;
    };
    throw new std::runtime_error("not valid body");
}

std::vector<Engine2D::Vector2D>& Engine2D::PolygonBody::getVertesies() const
{
    if(movementNotApplied)
    {
        applyVertesies();
        movementNotApplied = false;
    }
    return appliedVertecies;
}

void Engine2D::PolygonBody::applyVertesies() const
{
    for(size_t i = 0; i < localVertecies.size(); ++i)
    {
        appliedVertecies[i] = Transform::apply(Transform(position, rotation), localVertecies[i]);
    }
}
