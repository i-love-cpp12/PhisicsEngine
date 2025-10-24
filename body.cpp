#include "body.hpp"

Engine2D::Body::Body(const Vector2D& position, float rotation, BodyType type, const PhysicsProperties& properties):
    position(position),
    linearVelocity({0.0f, 0.0f}),
    rotation(rotation),
    angularVelocity(0.0f),
    properties(properties),
    type(type),
    movementNotApplied(true)
{
}

void Engine2D::Body::applyVelocity(float dt)
{
    moveBy(linearVelocity * dt);
    rotateBy(angularVelocity * dt);

    movementNotApplied = true;
}

void Engine2D::Body::addVelocity(const Vector2D &velocity)
{
    linearVelocity = linearVelocity + velocity;
}

void Engine2D::Body::moveTo(const Vector2D &newPos)
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

void Engine2D::Body::addForce(const Vector2D& amount)
{
    force = force + amount;
}

void Engine2D::Body::takeStep(float dt)
{
    linearVelocity = linearVelocity + force;
    force = Vector2D::ZERO();
    applyVelocity(dt);
}

Engine2D::CircleBody::CircleBody(const Vector2D& position, float radius, const PhysicsProperties& properties):
    Engine2D::Body::Body(position, 0.0f, circle, properties), radius(radius)
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
            return getCollisionCirclePolygon({position, radius}, {otherPolygon.getVertesies()});
        }
        break;
    };
    throw new std::runtime_error("not valid body");
}

Engine2D::PolygonBody::PolygonBody(const Vector2D &position, float width, float height, float rotation, const PhysicsProperties& properties):
    Engine2D::Body::Body(position, rotation, polygon, properties),
    localVertecies({
        Vector2D(-width / 2, -height / 2),
        Vector2D(width / 2, -height / 2),
        Vector2D(width / 2, height / 2),
        Vector2D(-width / 2, height / 2)
    })
{
    appliedVertecies.resize(localVertecies.size());
}

Engine2D::PolygonBody::PolygonBody(const Vector2D& position, const std::vector<Vector2D>& localVertecies, float rotation, const PhysicsProperties& properties):
    Engine2D::Body::Body(position, rotation, polygon, properties),
    localVertecies(localVertecies)
{
    appliedVertecies.resize(localVertecies.size());
}


void Engine2D::PolygonBody::draw(Color color, float strokeSize) const
{
    std::vector<Vector2D> vertesies = getVertesies();
    for(size_t i = 0; i < vertesies.size(); ++i)
    {
        DrawLineV(vertesies[i].toRaylibVector(), vertesies[(i + 1) % vertesies.size()].toRaylibVector(), color);
    }
}

Engine2D::Collision Engine2D::PolygonBody::getCollision(const Body &body) const
{
    switch(body.getType())
    {
        case circle:
        {
            const CircleBody& otherCircle = static_cast<const CircleBody&>(body);
            return getCollisionCirclePolygon({otherCircle.getPosition(), otherCircle.getRadius()}, {getVertesies()});
        }
        break;

        case polygon:
        {
            const PolygonBody& otherPolygon = static_cast<const PolygonBody&>(body);
            return getCollisionPolygonPolygon({getVertesies()}, {otherPolygon.getVertesies()});
        }
        break;
    };
    throw new std::runtime_error("not valid body");
}

const std::vector<Engine2D::Vector2D>& Engine2D::PolygonBody::getVertesies() const
{
    PolygonBody* self = const_cast<PolygonBody*>(this);
    if(movementNotApplied)
    {
        self->applyVertesies();
        self->movementNotApplied = false;
    }
    return self->appliedVertecies;
}

void Engine2D::PolygonBody::applyVertesies()
{
    Transform t = Transform(position, rotation);
    for(size_t i = 0; i < appliedVertecies.size(); ++i)
    {
        appliedVertecies[i] = Transform::apply(t, localVertecies[i]);
    }
}
