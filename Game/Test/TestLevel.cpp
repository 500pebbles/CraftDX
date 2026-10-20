#include "TestLevel.h"
#include "TestActor.h"
#include "Component/StaticMeshComponent.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/StaticMesh.h"

using namespace Craft;

void TestLevel::Initialized()
{
    Level::Initialized();
 
    // Caching Mesh Address.
    auto triangle = StaticMesh::CreateTriangleMesh();
    auto quad = StaticMesh::CreateQuadMesh();
    
    // Create Shader.
    auto shader = Shader::CreateDefaultShader();
    
    // Create Actors.
    auto left = SpawnActor<TestActor>();
    left->GetTransform().scale = Vector3::One * 0.4f;
    left->GetTransform().position.x = -0.5f;
    left->GetComponent<StaticMeshComponent>()->SetStaticMesh(quad);
    left->GetComponent<StaticMeshComponent>()->SetShader(shader);
    
    auto center = SpawnActor<TestActor>();
    center->GetTransform().scale = Vector3::One * 0.4f;
    center->GetTransform().position.x = 0.f;
    center->GetComponent<StaticMeshComponent>()->SetStaticMesh(quad);
    center->GetComponent<StaticMeshComponent>()->SetShader(shader);

    auto right = SpawnActor<TestActor>();
    right->GetTransform().scale = Vector3::One * 0.4f;
    right->GetTransform().position.x = 0.5f;
    right->GetComponent<StaticMeshComponent>()->SetStaticMesh(quad);
    right->GetComponent<StaticMeshComponent>()->SetShader(shader);
}

void TestLevel::Draw()
{
    Level::Draw();
    
    Vector3 eye (10.f, 0.f, 0.f);
    Vector3 target = eye + Vector3::Forward;
    Vector3 up = Vector3::Up;
    const Matrix4 view = Matrix4::LookAt(eye, target, up);
    
    Renderer::Get().SubmitCamera(view);
}
