#include "Shader.h"

#include <d3dcompiler.h>

#include "Renderer.h"
#include "Core/Core.h"

namespace Craft
{
    Shader::Shader(const std::wstring& shaderName)
    {
        // 셰이더 경로 생성
        std::wstring shaderFolder = L"HLSLShaders/";
        std::wstring vertexPath = shaderFolder + shaderName + std::wstring(L"VS.cso");
        std::wstring pixelPath = shaderFolder + shaderName + std::wstring(L"PS.cso");
        
        // 셰이더 컴파일 결과 저장용 객체
        ID3DBlob* vertexShaderObject = nullptr;
        
        ThrowIfFailed(
            D3DReadFileToBlob(vertexPath.c_str(), &vertexShaderObject),
            L"Failed to load vertex shader object.");
        
        auto& device = Renderer::Get().GetDevice();
        
        // 정점 셰이더 객체 생성
        ThrowIfFailed(
            device.CreateVertexShader(
                vertexShaderObject->GetBufferPointer(),
                vertexShaderObject->GetBufferSize(),
                nullptr,
                &vertexShader
            ), L"Failed to create vertex shader");

        // 정점 셰이더 입력 관련 정보 객체 생성
        D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        ThrowIfFailed(device.CreateInputLayout(
            inputLayoutDesc,
            _countof(inputLayoutDesc),
            vertexShaderObject->GetBufferPointer(),
            vertexShaderObject->GetBufferSize(),
            &inputLayout), L"failed to create input layout");


        // 픽셀 셰이더 컴파일 결과 저장용 객체
        ID3DBlob* pixelShaderObject = nullptr;
        
        ThrowIfFailed(
            D3DReadFileToBlob(pixelPath.c_str(), &pixelShaderObject),
            L"Failed to load pixel shader object.");
	
        // 픽셀 셰이더 객체 생성 
        ThrowIfFailed(
            device.CreatePixelShader(
                pixelShaderObject->GetBufferPointer(),
                pixelShaderObject->GetBufferSize(),
                nullptr,
                &pixelShader
            ), L"Failed to create pixel shader");

        // 사용한 리소스 해제
        SafeRelease(vertexShaderObject);
        SafeRelease(pixelShaderObject);
    }

    Shader::~Shader()
    {
        SafeRelease(vertexShader);
        SafeRelease(pixelShader);
        SafeRelease(inputLayout);
    }

    void Shader::Bind()
    {
        auto& context = Renderer::Get().GetContext();
      
        context.IASetInputLayout(inputLayout);
        context.VSSetShader(vertexShader, nullptr, 0);
        context.PSSetShader(pixelShader, nullptr, 0);    
    }

    std::shared_ptr<Shader> Shader::CreateDefaultShader()
    {
        return std::make_shared<Shader>(L"Default");
    }
}
