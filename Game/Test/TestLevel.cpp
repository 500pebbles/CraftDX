#include "TestLevel.h"
#include "TestActor.h"

using namespace Craft;

void TestLevel::Initialized()
{
    Level::Initialized();
    
    auto left = SpawnActor<TestActor>();
    left->GetTransform().scale = Vector3::One * 0.5f;
    left->GetTransform().position.x = -0.5f;
    
    auto right = SpawnActor<TestActor>();
    right->GetTransform().scale = Vector3::One * 0.5f;
    right->GetTransform().position.x = 0.5f;
}

