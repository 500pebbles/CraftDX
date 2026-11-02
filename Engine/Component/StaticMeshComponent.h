#pragma once
#include "Component.h"


namespace Craft
{
    class Material;
    class StaticMesh;

    class StaticMeshComponent : public Component
    {
    public:
        StaticMeshComponent() = default;
        ~StaticMeshComponent() = default;
        
        virtual void Draw() override;

        inline void SetStaticMesh(const std::shared_ptr<StaticMesh>& newStaticMesh) { staticMesh = newStaticMesh; }
        
        inline void SetMaterial(const std::shared_ptr<Material>& newMaterial) { material = newMaterial; }
        
    private:        
        std::shared_ptr<StaticMesh> staticMesh;
        
        std::shared_ptr<Material> material;
    };
}
