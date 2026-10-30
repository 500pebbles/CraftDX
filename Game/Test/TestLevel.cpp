#include "TestLevel.h"
#include "TestActor.h"
#include "Component/CameraComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Graphics/Shader.h"
#include "Graphics/StaticMesh.h"
#include "Graphics/Texture.h"

using namespace Craft;

void TestLevel::Initialized()
{
    Level::Initialized();
 
    // 텍스쳐.
    auto texture = Texture::Load("Assets/T_Checker.jpg");
    
    // Caching Mesh Address.
    auto triangle = StaticMesh::CreateTriangleMesh();
    auto quad = StaticMesh::CreateQuadMesh();
    
    // Create Shader.
    auto defaultShader = std::make_shared<Shader>(L"Yellow");
    auto yellowShader = std::make_shared<Shader>(L"Yellow");
    
    // Create Actors.
    auto left = SpawnActor<TestActor>();
    left->GetTransform().scale = Vector3::One * 0.4f;
    left->GetTransform().position.x = -0.5f;
    left->GetComponent<StaticMeshComponent>()->SetStaticMesh(quad);
    left->GetComponent<StaticMeshComponent>()->SetShader(defaultShader);
    left->GetComponent<StaticMeshComponent>()->SetTexture(texture);
    left->GetTransform().position.z = +1.f;
    
    auto right = SpawnActor<TestActor>();
    right->GetTransform().scale = Vector3::One * 0.4f;
    
    right->GetTransform().position.x = 0.5f;
    right->GetComponent<StaticMeshComponent>()->SetStaticMesh(triangle);
    right->GetComponent<StaticMeshComponent>()->SetShader(yellowShader);
    right->GetComponent<StaticMeshComponent>()->SetTexture(texture);
    
    // 카메라 컴포넌트를 생성하고, (그냥 액터 타입) 컴포넌트를 부착함.
    auto camera = SpawnActor<Actor>();
    camera->AddComponent<CameraComponent>();
    camera->GetTransform().position.z = -3.f;
}