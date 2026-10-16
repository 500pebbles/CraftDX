#include "TestActor.h"

#include "Component/StaticMeshComponent.h"
#include "Graphics/Renderer.h"

void TestActor::Initialized()
{
    Actor::Initialized();
    
    AddComponent<Craft::StaticMeshComponent>();
}

void TestActor::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    
    GetTransform().rotation.z += 60.f * deltaTime;
}