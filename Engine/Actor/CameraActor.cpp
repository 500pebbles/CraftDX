#include "EnginePCH.h"
#include "CameraActor.h"

#include "Component/CameraComponent.h"

namespace Craft
{
    void CameraActor::Initialized()
    {
        Actor::Initialized();
        
        cameraComponent = AddComponent<CameraComponent>();
    }

    void CameraActor::SetProjection(float fieldOfView, float nearDistance, float farDistance)
    {
        cameraComponent->SetProjection(fieldOfView, nearDistance, farDistance);
    }
}
