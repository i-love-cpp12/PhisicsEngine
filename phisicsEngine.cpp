#include "phisicsEngine.hpp"

Engine2D::PhisicsEngine::PhisicsEngine(const Vector2D &windowsSize, const std::string& title, unsigned short FPS)//: colors({WHITE, WHITE})
{
    InitWindow(windowsSize.x, windowsSize.y, title.c_str());
    SetTargetFPS(FPS);

    bodies.push_back(std::make_unique<CircleBody>(Vector2D{100.0f, 100.0f}, 50.0f, 1.0f));
    bodies.push_back(std::make_unique<CircleBody>(Vector2D{700.0f, 300.0f}, 50.0f, 10.0f));
    bodies.push_back(std::make_unique<CircleBody>(Vector2D{700.0f, 300.0f}, 50.0f, 20.0f));
    bodies.push_back(std::make_unique<CircleBody>(Vector2D{700.0f, 300.0f}, 50.0f, 100.0f));
}

Engine2D::PhisicsEngine::~PhisicsEngine()
{
    CloseWindow();
}

void Engine2D::PhisicsEngine::update()
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
            Collision collision = bodies[i]->getCollision(*bodies[j]);

            bodies[i]->moveBy(collision.normal * (collision.collisonDepth * 0.5f));
            bodies[j]->moveBy(-collision.normal * (collision.collisonDepth * 0.5f));
        }
    }
}

void Engine2D::PhisicsEngine::draw() const
{
    BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(10, 10);
        for(size_t i = 0; i < bodies.size(); ++i)
        {
            bodies[i]->draw(WHITE, 5.0f);
            DrawCircleV(bodies[i]->getPosition().toRaylibVector(), 6.0f, GREEN);
        }
    EndDrawing();
}
