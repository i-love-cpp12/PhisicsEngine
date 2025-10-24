#pragma once

namespace Engine2D
{
    class PhysicsProperties
    {
        public:
            PhysicsProperties(float mass = 1.0f, float restitution = 0.5f, bool isStatic = false, float dencity = 1.0f);
            float mass;//kg
            float dencity;//kg/m 
            float restitution;// 0-1
            bool isStatic;//bool
    };
};