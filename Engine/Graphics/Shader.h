#pragma once
#include <d3d11.h>
#include <memory>
#include <string>

namespace Craft
{    
    class Shader
    {
    public:
        Shader(const std::wstring& shaderName);
        ~Shader();
        
    public:
        void Bind();
        
        static std::shared_ptr<Shader> CreateDefaultShader();
        
    private:
        ID3D11VertexShader* vertexShader = nullptr;
        ID3D11PixelShader* pixelShader = nullptr;
        ID3D11InputLayout* inputLayout = nullptr;
    };
}
