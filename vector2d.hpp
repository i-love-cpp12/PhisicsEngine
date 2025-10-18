#pragma once

#include<raylib.h>
#include"printable.hpp"

namespace Engine2D
{
    class Vector2D: public Printable
    {
        public:
            float x, y;

            Vector2D(float x, float y);
            Vector2D(const Vector2D& vec) = default;
            Vector2D();

            static Vector2D ZERO();

            Vector2 toRaylibVector() const;

            float getLength() const;

            bool isEqual(const Vector2D &other) const;
            bool operator==(const Vector2D &other) const;
            bool operator!=(const Vector2D &other) const;

            Vector2D add(const Vector2D &other) const;
            Vector2D operator+(const Vector2D &other) const;

            Vector2D subtract(const Vector2D &other) const;
            Vector2D operator-(const Vector2D &other) const;

            Vector2D toggleSign() const;
            Vector2D operator-() const;

            Vector2D multiply(const Vector2D &other) const;
            Vector2D operator*(const Vector2D &other) const;

            Vector2D multiply(float scalar) const;
            Vector2D operator*(float scalar) const;
        
            float distance(const Vector2D &other) const;

            Vector2D getNormalized() const;
            
            float getDotProduct(const Vector2D &other) const;

            Vector2D perp() const;
        private:
            std::ostream& print(std::ostream& stream) const override;
    };
};