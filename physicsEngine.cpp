#include "physicsEngine.hpp"

Engine2D::PhysicsEngine::PhysicsEngine(const Vector2D &windowsSize, const std::string& title, unsigned short FPS): colors({BLACK, BLACK, BLACK})
{
    InitWindow(windowsSize.x, windowsSize.y, title.c_str());
    SetTargetFPS(FPS);

    // bodies.push_back(std::make_unique<PolygonBody>(Vector2D{100.0f, 100.0f}, 100.0f, 130.0f, 0.0f, PhysicsProperties{1.0f}));
    // bodies.push_back(std::make_unique<PolygonBody>(Vector2D{500.0f, 100.0f}, 100.0f, 150.0f, 0.0f, PhysicsProperties{1.0f}));
    bodies.push_back(std::make_unique<PolygonBody>(Vector2D{100.0f, 100.0f}, 100.0f, 130.0f, 0.0f, 
        PhysicsProperties{1.0f, 0.5f}));
    bodies.push_back(std::make_unique<PolygonBody>(Vector2D{500.0f, 100.0f}, 100.0f, 150.0f, 0.0f, 
        PhysicsProperties{200.0f, 0.8f}));
    bodies.push_back(std::make_unique<CircleBody>(Vector2D{700.0f, 100.0f}, 50.0f, PhysicsProperties{1.0f}));
}

Engine2D::PhysicsEngine::~PhysicsEngine()
{
    CloseWindow();
}

void Engine2D::PhysicsEngine::takeStep()
{
    Vector2D input =
        Vector2D((float)(IsKeyDown(KEY_D)) - (float)(IsKeyDown(KEY_A)),
                (float)(IsKeyDown(KEY_S)) - (float)(IsKeyDown(KEY_W)))
                .getNormalized();
    const float SPEED = 200.0f;
    const float dt = GetFrameTime();

    bodies[0]->addVelocity(input * SPEED * dt);
    bodies[1]->rotateBy(10.0f * dt);

    for(size_t i = 0; i < bodies.size(); ++i)
    {
        bodies[i]->takeStep(dt);
    }

    for(size_t i = 0; i < bodies.size() - 1; ++i)
    {
        for(size_t j = i + 1; j < bodies.size(); ++j)
        {
            // colors[i] = BLACK;
            // colors[j] = BLACK;
            Body* bodyA = bodies[i].get();
            Body* bodyB = bodies[j].get();
            Collision collision = bodyA->getCollision(*bodyB);
            
            resolveCollision(bodyA, bodyB, collision);
        }
    }
}

void Engine2D::PhysicsEngine::resolveCollision(Body *bodyA, Body *bodyB, const Collision &collision)
{
    if(collision.isCollision)
    {
        bodyA->moveBy(collision.normal * collision.collisonDepth);
        bodyB->moveBy(-collision.normal * collision.collisonDepth);
    }
    //------------------------
    // if(!collision.isCollision) return;
    
    // bodyA->moveBy(collision.normal * collision.collisonDepth);
    // bodyB->moveBy(-collision.normal * collision.collisonDepth);

    // Vector2D relativeVelocity = bodyB->getLinearVelocity() - bodyA->getLinearVelocity();

    // float e = min<float>(bodyA->getProperties().restitution, bodyB->getProperties().restitution);

    // float j = -(1.0f + e) * relativeVelocity.getDotProduct(collision.normal);

    // bodyA->addVelocity(collision.normal * bodyA->getProperties().mass * (1 / j));
    // bodyB->addVelocity(-(collision.normal * bodyA->getProperties().mass * (1 / j)));
}

void Engine2D::PhysicsEngine::draw() const
{
    BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(10, 10);
        for(size_t i = 0; i < bodies.size(); ++i)
        {
            bodies[i]->draw(BLACK, 5.0f);
            DrawCircleV(bodies[i]->getPosition().toRaylibVector(), 2.0f, GREEN);
        }
    EndDrawing();
}
