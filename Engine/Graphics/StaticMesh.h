#pragma once
#include <cstdint>
#include <d3d11.h>
#include <memory>
#include <vector>

#include "Math/Vector3.h"

namespace Craft
{    
    class StaticMesh
    {
    public:
        StaticMesh(const std::vector<Vector3> vertices, const std::vector<uint32_t> indices);
        ~StaticMesh();
        
    public:
        void Bind() const;
        
        static std::shared_ptr<StaticMesh> CreateTriangleMesh();
        static std::shared_ptr<StaticMesh> CreateQuadMesh();
        
    public:
        uint32_t GetIndexCount() const { return indexCount; }
        
    private:
        ID3D11Buffer* vertexBuffer = nullptr;
        ID3D11Buffer* indexBuffer = nullptr;
        uint32_t indexCount = 0;
        uint32_t stride = 0;
    };
}
