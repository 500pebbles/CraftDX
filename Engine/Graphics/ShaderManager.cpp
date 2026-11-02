#include "EnginePCH.h"
#include "ShaderManager.h"

#include "Shader.h"

namespace Craft
{
    std::shared_ptr<Shader> ShaderManager::LoadShader(const std::wstring& name)
    {
        auto result = shaders.find(name);
        if (result != shaders.end())
        {
            return result->second;
        }
        
        auto newShader = std::make_shared<Shader>(name);
        shaders.emplace(name, newShader);
        
        return newShader;        
    }
}
