#pragma once
#include <unordered_map>

#include "Core/Core.h"

namespace Craft
{
    class Shader;

    class ShaderManager : public TGlobalAccessible<ShaderManager>
    {
    public:
        ShaderManager() = default;
        ~ShaderManager() = default;
        
        std::shared_ptr<Shader> LoadShader(const std::wstring& name);
        
    private:
        std::unordered_map<std::wstring, std::shared_ptr<Shader>> shaders;
    };
}
    
