#include "TestActor.h"

void TestActor::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    
    GetTransform().rotation.z += 60.f * deltaTime;
}
