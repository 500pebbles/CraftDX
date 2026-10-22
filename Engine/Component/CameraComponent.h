#pragma once
#include "Component.h"

namespace Craft
{
    class CameraComponent : public Component
    {
    public:
        CameraComponent() = default;
        ~CameraComponent() = default;
        
    public:
        virtual void Draw() override;
        
        void SetProjection(float fieldOfView, float nearDistance = 0.1f, float farDistance = 1000.f);
        
    private: 
        float fieldOfView = 60.f;
        
        float nearDistance = 0.1f;
        
        float farDistance = 1000.f;
    };    
}

