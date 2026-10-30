#pragma once

namespace Craft
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();
        
        void Bind(uint32_t slot = 0) const;
        
        static std::shared_ptr<Texture> Load(const std::string& path);
   
    private:
        void LoadFromFile(const std::string& path);
        
    private:
        uint32_t width = 0;
        uint32_t height = 0;
        
        ID3D11Texture2D* texture = nullptr;
        
        ID3D11ShaderResourceView* shaderResourceView = nullptr;
        
        ID3D11SamplerState* samplerState = nullptr;
    };
}