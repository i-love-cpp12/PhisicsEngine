#include "phyisicsEngine.hpp"

Engine2D::PhyisicsEngine::PhyisicsEngine(const Vector2D &windowsSize, const std::string& title, unsigned short FPS): colors({BLACK, BLACK})
{
    InitWindow(windowsSize.x, windowsSize.y, title.c_str());
    SetTargetFPS(FPS);

    bodies.push_back(std::make_unique<PolygonBody>(Vector2D{100.0f, 100.0f}, 200.0f, 300.0f, 0.0f, 1.0f));
    bodies.push_back(std::make_unique<PolygonBody>(Vector2D{200.0f, 100.0f}, 100.0f, 150.0f, 45.0f, 1.0f));
}

Engine2D::PhyisicsEngine::~PhyisicsEngine()
{
    CloseWindow();
}

void Engine2D::PhyisicsEngine::update()
{
    Vector2D input =
        Vector2D((float)(IsKeyDown(KEY_D)) - (float)(IsKeyDown(KEY_A)),
                (float)(IsKeyDown(KEY_S)) - (float)(IsKeyDown(KEY_W)))
                .getNormalized();
    const float SPEED = 200.0f;
    const float dt = GetFrameTime();

    bodies[0]->moveBy(input * SPEED * dt);

    for(size_t i = 0; i < bodies.size() - 1; ++i)
    {
        for(size_t j = i + 1; j < bodies.size(); ++j)
        {
            colors[i] = BLACK;
            colors[j] = BLACK;

            Collision collision = bodies[i]->getCollision(*bodies[j]);

            // bodies[i]->moveBy(collision.normal * (collision.collisonDepth * 0.5f));
            // bodies[j]->moveBy(-collision.normal * (collision.collisonDepth * 0.5f));
            bodies[i]->rotateBy(0.5f);

            if(collision.isCollision)
            {
                colors[i] = RED;
                colors[j] = RED;
            }
        }
    }
}

void Engine2D::PhyisicsEngine::draw() const
{
    BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(10, 10);
        for(size_t i = 0; i < bodies.size(); ++i)
        {
            bodies[i]->draw(colors[i % colors.size()], 5.0f);
            DrawCircleV(bodies[i]->getPosition().toRaylibVector(), 2.0f, GREEN);
        }
    EndDrawing();
}
