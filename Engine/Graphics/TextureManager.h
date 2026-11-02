#pragma once
#include <unordered_map>

#include "Texture.h"
#include "Core/Core.h"

namespace Craft
{
    class TextureManager : public TGlobalAccessible<TextureManager>
    {
    public:
        TextureManager() = default;
        ~TextureManager() = default;
        
        std::shared_ptr<Texture> LoadTexture(const std::string& texturePath);
        
    private:
        std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    
    };    
}

