#include "EnginePCH.h"
#include "Texture.h"
#include "Core/Core.h"

#define STB_IMAGE_IMPLEMENTATION
#include <ThirdParty/stb_image.h>

#include "Renderer.h"

namespace Craft
{
    Texture::Texture(const std::string& path)
    {
        LoadFromFile(path);
    
    }

    Texture::~Texture()
    {
        SafeRelease(texture);
        SafeRelease(shaderResourceView);
        SafeRelease(samplerState);
    }

    void Texture::Bind(uint32_t slot) const
    {
        auto& context = Renderer::Get().GetContext();
        context.PSSetShaderResources(slot, 1, &shaderResourceView);
        context.PSSetSamplers(slot, 1, &samplerState);
    }

    std::shared_ptr<Texture> Texture::Load(const std::string& path)
    {
        return std::make_shared<Texture>(path);
    }

    void Texture::LoadFromFile(const std::string& path)
    {
        // 이미지 OUT 프로퍼티 
        int imageWidth = 0;
        int imageHeight = 0;
        int channelCount = 0;
        
        // 이미지를 로드해서 버퍼에 저장
        stbi_uc* pixels = stbi_load(path.c_str(), &imageWidth, &imageHeight, &channelCount, STBI_rgb_alpha);
        if (!pixels)
        {
            assert(false);
            return;
        }
        
        // 이미지 크기 멤버변수에 캐싱. 
        width = static_cast<uint32_t>(imageWidth);
        height = static_cast<uint32_t>(imageHeight);
        
        auto& device = Renderer::Get().GetDevice();
        
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        
        D3D11_SUBRESOURCE_DATA textureData = {};
        textureData.pSysMem = pixels;
        textureData.SysMemPitch = width * 4;
        
        auto result = device.CreateTexture2D(&textureDesc, &textureData, &texture);
        
        stbi_image_free(pixels); // 로드한 이미지 메모리에서 해제.

        ThrowIfFailed(
            result,
            L"Failed to create Texture2D.");
       
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        srvDesc.Texture2D.MostDetailedMip = 0;
        
        ThrowIfFailed( 
            device.CreateShaderResourceView(texture, &srvDesc, &shaderResourceView),
            L"Failed to create shader resource view.");
        
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.MinLOD = 0.f;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
        
        ThrowIfFailed(
        device.CreateSamplerState(&samplerDesc, &samplerState),
        L"Failed to create sampler state."
        );
        
        
       
    }
}
