#pragma once

#include"vector2d.hpp"
#include"collisions.hpp"
#include"transform.hpp"
#include<vector>
#include<array>

namespace Engine2D
{
    enum BodyType
    {
        circle = 0,
        rectangle = 1,
        polygon = 2
    };
    class Body
    {
        protected:
            Body(const Vector2D& position, float weight, BodyType type, bool isStatic = false, float rotation = 0.0f, float dencity = 1.0f, float restitution = 0.5f);
            Vector2D position;//m
            Vector2D linearVelocity;//m/s
            float rotation;//deg
            float angularVelocity;//deg/s
            float weight;//kg
            float dencity;//kg/m 
            float restitution;// 0-1
            bool isStatic;
            BodyType type;
            bool movementNotApplied;
        public:
            virtual void draw(Color color = WHITE, float strokeSize = 0.0f) const = 0;
            virtual Collision getCollision(const Body& body) const = 0;
            BodyType getType() const {return type;}
            Vector2D getPosition() const {return position;}
            float getWeight() const {return weight;}
            void moveTo(const Vector2D& newPos);
            void moveBy(const Vector2D& amount);
            void rotate(float amount);
    };

    class CircleBody: public Body
    {
        public:
            CircleBody(const Vector2D& position, float radius, float weight, bool isStatic = false, float dencity = 1.0f, float restitution = 0.5f);
            void draw(Color color = WHITE, float strokeSize = 0.0f) const override;
            Collision getCollision(const Body& body) const override;
            float getRadius() const {return radius;}
        private:
            float radius;
    };

    class RectangleBody: public Body
    {
        public:
            RectangleBody(const Vector2D& position, float width, float height, float weight, bool isStatic = false, float dencity = 1.0f, float restitution = 0.5f);
            void draw(Color color = WHITE, float strokeSize = 0.0f) const override;
            Collision getCollision(const Body& body) const override;
        private:
            std::array<Vector2D, 4>& getVertices();
            void applyVertecies();
            float width;
            float height;
            std::array<Vector2D, 4> appliedVertecies;
            std::array<Vector2D, 4> localVertecies;
    };
};
