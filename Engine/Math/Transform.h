#pragma once

#include "Core/Core.h"
#include "Matrix4.h"

namespace Craft
{    
    class Transform
    {
    public:
        Transform();
        ~Transform() = default;
        
    public:
        void Update();
        
    public:
        Vector3 Right() const;
        Vector3 Up() const;
        Vector3 Forward() const;
        
        const Matrix4& GetWorldMatrix() const { return worldMatrix; }
    
    public:
        Vector3 position = Vector3::Zero;
        Vector3 rotation = Vector3::Zero;
        Vector3 scale = Vector3::One;   
        
    private:
        Matrix4 worldMatrix;
    
    };
}