#pragma once

#include"vector2d.hpp"
#include"collisions.hpp"
#include"transform.hpp"
#include"physicsProperties.hpp"
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
            Body(const Vector2D& position, float rotation, BodyType type, const PhysicsProperties& properties);
            Vector2D position;//m
            Vector2D linearVelocity;//m/s
            float rotation;//deg
            float angularVelocity;//deg/s
            PhysicsProperties properties;
            
            BodyType type;
            bool movementNotApplied;
            void applyVelocity(float dt);
        public:
            virtual ~Body() = default;
            virtual void draw(Color color = WHITE, float strokeSize = 0.0f) const = 0;
            virtual Collision getCollision(const Body& body) const = 0;
            BodyType getType() const {return type;}
            Vector2D getPosition() const {return position;}
            float getWeight() const {return properties.weight;}
            void moveTo(const Vector2D& newPos);
            void moveBy(const Vector2D& amount);
            void rotateTo(float newRotation);
            void rotateBy(float amount);
            void addForce(const Vector2D force);
            void takeStep(float dt);
    };

    class CircleBody: public Body
    {
        public:
            CircleBody(const Vector2D& position, float radius, const PhysicsProperties& properties);

            void draw(Color color = WHITE, float strokeSize = 0.0f) const override;
            Collision getCollision(const Body& body) const override;

            float getRadius() const {return radius;}
        private:
            float radius;
    };

    class PolygonBody: public Body
    {
        public:
            PolygonBody(const Vector2D& position, float width, float height, float rotation, const PhysicsProperties& properties);

            PolygonBody(const Vector2D& position, const std::vector<Vector2D>& localVertecies, float rotation, const PhysicsProperties& properties);

            void draw(Color color = WHITE, float strokeSize = 0.0f) const override;
            Collision getCollision(const Body& body) const override;
            const std::vector<Vector2D>& getVertesies() const;
        private:
            void applyVertesies();
            std::vector<Vector2D> localVertecies;
            std::vector<Vector2D> appliedVertecies;
    };
};
