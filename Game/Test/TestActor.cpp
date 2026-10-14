#include "TestActor.h"

#include "Graphics/Renderer.h"

void TestActor::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    
    GetTransform().rotation.z += 60.f * deltaTime;
}

void TestActor::Draw()
{
    Actor::Draw();
    Craft::Transform& transform = GetTransform();
    Craft::Renderer::Get().Submit(staticMesh, transform.GetWorldMatrix());
}
