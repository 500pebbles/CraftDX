#include "EnginePCH.h"
#include "TextureManager.h"

namespace Craft
{
    std::shared_ptr<Texture> TextureManager::LoadTexture(const std::string& texturePath)
    {
        auto result = textures.find(texturePath);
        if (result != textures.end())
        {
            return result->second;
        }
        
        auto newTexture = Texture::Load(texturePath);
        textures.emplace(texturePath, newTexture);
        
        return newTexture;
    }
}