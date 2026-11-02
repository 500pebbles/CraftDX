#include "EnginePCH.h"
#include "Material.h"

#include "Shader.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace Craft
{
    void Material::Bind() const
    {
    }

    DefaultMaterial::DefaultMaterial()
        : shader(ShaderManager::Get().LoadShader(L"Default"))
    {
        
    }

    void DefaultMaterial::Bind() const
    {
        shader->Bind();
    }

    TextureMappingMaterial::TextureMappingMaterial(const std::string& texturePath)
        : shader(ShaderManager::Get().LoadShader(L"TextureMapping")), texture(TextureManager::Get().LoadTexture(texturePath))
    {
    }

    void TextureMappingMaterial::Bind() const
    {
        shader->Bind();
        texture->Bind(0);
    }
}
