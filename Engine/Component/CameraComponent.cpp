#include "EnginePCH.h"
#include "CameraComponent.h"

#include "Core/Engine.h"
#include "GameFramework/Actor.h"
#include "Graphics/Renderer.h"
#include "Math/Transform.h"

namespace Craft
{
    void CameraComponent::Draw()
    {
        Component::Draw();
        
        auto actor = GetOwner();
        const Transform& transform = actor->GetTransform();
        
        // 카메라 좌표계변환.
        Matrix4 view = Matrix4::InverseTranslationRotation(transform.position, transform.rotation);
    
        // 투영 좌표계변환.
        float width = static_cast<float>(Engine::Get().GetClientWidth());
        float height = static_cast<float>(Engine::Get().GetClientHeight());
        if (width == 0.f || height == 0.f) return;
        
        Matrix4 projection = Matrix4::Perspective(fieldOfView,
        width,
        height,
        nearDistance,
        farDistance);
        
        // Submit.
        Renderer::Get().SubmitCamera(view, projection);
    } 

    void CameraComponent::SetProjection(float fieldOfView, float nearDistance, float farDistance)
    {
        this->fieldOfView = fieldOfView;        
        this->nearDistance = nearDistance;        
        this->farDistance = farDistance;
    }
}
