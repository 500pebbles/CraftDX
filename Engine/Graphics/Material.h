#pragma once

#include <memory>
#include <string>

namespace Craft
{
    class Shader; 
    class Texture; 
    
    class Material
    {
    public:
        Material() = default;
        virtual ~Material() = default;
        
        virtual void Bind() const;
    };
    
    class DefaultMaterial : public Material
    {
    public:
        DefaultMaterial();
        ~DefaultMaterial() = default;
        
    private:
        virtual void Bind() const override;
        
    private:
        std::shared_ptr<Shader> shader;
    };
    
    class TextureMappingMaterial : public Material
    {
    public:
        TextureMappingMaterial(const std::string& texturePath);
        ~TextureMappingMaterial() = default;
        
    private:
        virtual void Bind() const override;
        
    private:
        std::shared_ptr<Shader> shader;
        
        std::shared_ptr<Texture> texture;
    };
    
}