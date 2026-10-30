#pragma once
#include "Component.h"


namespace Craft
{
    class Texture;
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
        
        inline void SetTexture(const std::shared_ptr<Texture>& newTexture) { texture = newTexture; }
        
    private:        
        std::shared_ptr<StaticMesh> staticMesh;
        
        std::shared_ptr<Shader> shader;
        
        std::shared_ptr<Texture> texture;
    };
}
