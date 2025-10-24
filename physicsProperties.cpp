#include "physicsProperties.hpp"

Engine2D::PhysicsProperties::PhysicsProperties(float mass, float restitution, bool isStatic, float dencity):
    mass(mass),
    dencity(dencity),
    restitution(restitution),
    isStatic(isStatic)
{
}