#include "TransformComponent.h"

#include "Graphics/Renderer.h"

namespace Craft
{
    void TransformComponent::Draw()
    {
        Component::Draw();
        
        // 월드 매트릭스를 업데이트하고 렌더러에 제출
        transform.Update();        
        Renderer::Get().Submit(transform.GetWorldMatrix());
    }
}
