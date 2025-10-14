#pragma once

namespace Engine2D
{
    class PhysicsProperties
    {
        public:
            PhysicsProperties(float weight, bool isStatic = false, float rotation = 0.0f, float dencity = 1.0f, float restitution = 0.5f);
            float weight;//kg
            float dencity;//kg/m 
            float restitution;// 0-1
            bool isStatic;//bool
    };
};