#pragma once
#include "Component.h"
#include "Math/Transform.h"


namespace Craft
{    
    class TransformComponent : public Component
    {
    public:
        TransformComponent() = default;
        ~TransformComponent() = default;
        
    public:
        virtual void Draw() override;
        
    public:
        Transform& GetTransform() { return transform; }
        const Transform& GetTransform() const { return transform; }
        
    private:
        Transform transform;
    };
}