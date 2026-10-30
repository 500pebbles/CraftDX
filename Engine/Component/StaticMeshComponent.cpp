#include "StaticMeshComponent.h"

#include <algorithm>
#include "GameFramework/Actor.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Math/Transform.h"

namespace Craft
{
    void StaticMeshComponent::Draw()
    {
        Component::Draw();
        
        auto actor = GetOwner();
        if (!actor || !shader || !staticMesh) return;
        
        const Transform& transform = actor->GetTransform();
        
        Renderer::Get().Submit(staticMesh, shader, texture, transform.GetWorldMatrix());
    }
}
