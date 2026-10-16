#pragma once
#include "Component.h"


namespace Craft
{
    class Shader;
    class StaticMesh;

    class StaticMeshComponent : public Component
    {
    public:
        StaticMeshComponent() = default;
        ~StaticMeshComponent() = default;
        
        virtual void Draw() override;

        inline void SetStaticMesh(const std::shared_ptr<StaticMesh>& newStaticMesh) { staticMesh = newStaticMesh; }
        
        inline void SetShader(const std::shared_ptr<Shader>& newShader) { shader = newShader; }
        
    private:        
        std::shared_ptr<StaticMesh> staticMesh;
        
        std::shared_ptr<Shader> shader;
    };
}
