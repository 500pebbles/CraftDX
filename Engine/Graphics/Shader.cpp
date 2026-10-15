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
        std::wstring vertexPath = shaderFolder + shaderName + std::wstring(L"VS.hlsl");
        std::wstring pixelPath = shaderFolder + shaderName + std::wstring(L"PS.hlsl");
        
        // 셰이더 컴파일 결과 저장용 객체
        ID3DBlob* vertexShaderObject = nullptr;

        // 셰이더(Shader) 컴파일
        ThrowIfFailed(D3DCompileFromFile(
            vertexPath.c_str(),
            nullptr,
            nullptr,
            "main",
            "vs_5_0",
            0,
            0,
            &vertexShaderObject,
            nullptr
        ), L"Failed to compile vertex shader");

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
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        ThrowIfFailed(device.CreateInputLayout(
            inputLayoutDesc,
            _countof(inputLayoutDesc),
            vertexShaderObject->GetBufferPointer(),
            vertexShaderObject->GetBufferSize(),
            &inputLayout), L"failed to create input layout");


        // 픽셀 셰이더 컴파일 결과 저장용 객체
        ID3DBlob* pixelShaderObject = nullptr;
	
        // 픽셀 셰이더
        ThrowIfFailed(D3DCompileFromFile(
            pixelPath.c_str(),
            nullptr,
            nullptr,
            "main",
            "ps_5_0",
            0,
            0,
            &pixelShaderObject,
            nullptr
        ), L"Failed to compile pixel shader");

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
