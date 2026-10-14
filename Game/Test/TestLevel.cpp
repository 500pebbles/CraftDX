#include "TestLevel.h"
#include "TestActor.h"
#include "Graphics/StaticMesh.h"

using namespace Craft;

void TestLevel::Initialized()
{
    Level::Initialized();
 
    // Caching Mesh Address.
    auto triangle = StaticMesh::CreateTriangleMesh();
    auto quad = StaticMesh::CreateQuadMesh();
    
    // Create Actors.
    auto left = SpawnActor<TestActor>();
    left->GetTransform().scale = Vector3::One * 0.4f;
    left->GetTransform().position.x = -0.5f;
    left->SetStaticMesh(quad);
    
    auto center = SpawnActor<TestActor>();
    center->GetTransform().scale = Vector3::One * 0.4f;
    center->GetTransform().position.x = 0.f;
    center->SetStaticMesh(quad); 

    auto right = SpawnActor<TestActor>();
    right->GetTransform().scale = Vector3::One * 0.4f;
    right->GetTransform().position.x = 0.5f;
    right->SetStaticMesh(triangle);
}

