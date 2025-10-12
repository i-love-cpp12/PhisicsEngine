#pragma once

#include<cmath>
#include"vector2d.hpp"

namespace Engine2D
{
    class Transform
    {
        public:
            Vector2D rotationCenter;
            float cos;
            float sin;
            Transform(const Vector2D& rotationCenter, float rotation);
            static Vector2D apply(const Transform &transform, const Vector2D& localPoint); 
    };
};