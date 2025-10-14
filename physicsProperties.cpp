#include "physicsProperties.hpp"

Engine2D::PhysicsProperties::PhysicsProperties(float weight, bool isStatic, float rotation, float dencity, float restitution):
    weight(weight),
    dencity(dencity),
    restitution(restitution),
    isStatic(isStatic)
{
}