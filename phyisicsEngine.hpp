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
    class PhyisicsEngine
    {
        public:
            PhyisicsEngine(const Vector2D& windowsSize, const std::string& title, unsigned short FPS);
            ~PhyisicsEngine();
            void draw() const;
            void update();
        private:
            std::vector<std::unique_ptr<PolygonBody>> bodies;
            std::vector<Color> colors;
    };
};