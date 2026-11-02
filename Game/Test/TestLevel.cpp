#include "TestLevel.h"
#include "TestActor.h"
#include "Actor/CameraActor.h"
#include "Component/StaticMeshComponent.h"
#include "Graphics/Material.h"
#include "Graphics/ShaderManager.h"
#include "Graphics/StaticMesh.h"
#include "Graphics/TextureManager.h"

using namespace Craft;

void TestLevel::Initialized()
{
    Level::Initialized();
 
    // 텍스쳐.
    auto texture = TextureManager::Get().LoadTexture("Assets/T_Chara.jpg");
    
    // Caching Mesh Address.
    auto triangle = StaticMesh::CreateTriangleMesh();
    auto quad = StaticMesh::CreateQuadMesh();
       
    
    auto defaultMaterial = std::make_shared<DefaultMaterial>();
    auto textureMappingMaterial = std::make_shared<TextureMappingMaterial>("Assets/T_Chara.jpg");
    
    // Create Actors.
    auto left = SpawnActor<TestActor>();
    left->GetTransform().scale = Vector3::One * 0.4f;
    left->GetTransform().position.x = -0.5f;
    left->GetComponent<StaticMeshComponent>()->SetStaticMesh(quad);
    left->GetComponent<StaticMeshComponent>()->SetMaterial(defaultMaterial);
    left->GetTransform().position.z = +1.f;
    
    auto right = SpawnActor<TestActor>();
    right->GetTransform().scale = Vector3::One * 0.4f;
    
    right->GetTransform().position.x = 0.5f;
    right->GetComponent<StaticMeshComponent>()->SetStaticMesh(triangle);
    right->GetComponent<StaticMeshComponent>()->SetMaterial(textureMappingMaterial);
    
    // 카메라 컴포넌트를 생성하고, (그냥 액터 타입) 컴포넌트를 부착함.
    auto camera = SpawnActor<CameraActor>();
    camera->GetTransform().position.z = -3.f;
}