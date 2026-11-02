#include "StaticMesh.h"

#include "Renderer.h"
#include "Vertex.h"

namespace Craft
{
    StaticMesh::StaticMesh(const std::vector<Vertex> vertices, const std::vector<uint32_t> indices)
    {
        assert(vertices.size() > 0 && indices.size() > 0);
        
        // 메쉬의 정점 정보 초기화
        indexCount = static_cast<uint32_t>(indices.size());
        stride = sizeof(vertices[0]);
        
        // Device 캐싱
        auto& device = Renderer::Get().GetDevice();
        

        /* Step 2 : 원시데이터를 GPU가 읽을수 있도록 버퍼로 포장해서 전달 */
        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = static_cast<uint32_t>(stride * vertices.size());
        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT; 
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    	
        D3D11_SUBRESOURCE_DATA vertexBufferData = {};	
        vertexBufferData.pSysMem = vertices.data();
    	
        /* Step 3 : device가 버퍼 생성 */
        ThrowIfFailed(
            device.CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer),
            L"Failed to create vertex buffer");
    	
    	
        /* Step 2 : 원시데이터를 GPU가 읽을수 있도록 버퍼로 포장해서 전달 */
        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(uint32_t) * static_cast<uint32_t>(indices.size()); 
        indexBufferDesc.Usage = D3D11_USAGE_DEFAULT; 
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    	
        D3D11_SUBRESOURCE_DATA indexBufferData = {};	
        indexBufferData.pSysMem = indices.data();
    	
        /* Step 3 : device가 버퍼 생성 */
        ThrowIfFailed(
            device.CreateBuffer(&indexBufferDesc, &indexBufferData, &indexBuffer),
            L"Failed to create vertex buffer");
    }

    StaticMesh::~StaticMesh()
    {
        SafeRelease(vertexBuffer);
        SafeRelease(indexBuffer);
    }

    void StaticMesh::Bind() const
    {
        // DeviceContext Caching.
        auto& context = Renderer::Get().GetContext();

        uint32_t offset = 0;
        context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);    	
        context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    std::shared_ptr<StaticMesh> StaticMesh::CreateTriangleMesh()
    {
        return std::make_shared<StaticMesh>(
         std::vector<Vertex> {
             Vertex{ Vector3(0.0f, 0.5f, 0.5f), Vector2(0.5f, 0.0f) },
             Vertex{ Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 1.0f) },
             Vertex{ Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 1.0f) }
         },
         std::vector<uint32_t> { 0, 1, 2 }
     );
    }

    std::shared_ptr<StaticMesh> StaticMesh::CreateQuadMesh()
    {
        return std::make_shared<StaticMesh>(
         std::vector<Vertex> {
             Vertex { Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f) },
             Vertex { Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f) },
             Vertex { Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 1.0f) },
             Vertex{ Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 1.0f) },
         },
         std::vector<uint32_t> { 0, 1, 2, 0, 2, 3 }
     );
    }
}
