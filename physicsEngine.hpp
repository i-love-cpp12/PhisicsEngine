#pragma once


#include<string>
#include<vector>
#include<memory>
#include<iostream>
#include"vector2d.hpp"
#include"body.hpp"
#include"collisions.hpp"

namespace Engine2D
{
    class PhysicsEngine
    {
        public:
            PhysicsEngine(const Vector2D& windowsSize, const std::string& title, unsigned short FPS);
            ~PhysicsEngine();
            void draw() const;
            void takeStep();
        private:
            void resolveCollision(Body* bodyA, Body* bodyB, const Collision& collision);
            std::vector<std::unique_ptr<Body>> bodies;
            std::vector<Color> colors;
    };
};