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
    class PhisicsEngine
    {
        public:
            PhisicsEngine(const Vector2D& windowsSize, const std::string& title, unsigned short FPS);
            ~PhisicsEngine();
            void draw() const;
            void update();
        private:
            std::vector<std::unique_ptr<Body>> bodies;
            // std::vector<Color> colors;
    };
};