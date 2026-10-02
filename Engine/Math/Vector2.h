#pragma once
#include <Core/Core.h>

namespace Craft
{
    class Vector2
    {
    public:
        Vector2(float x = 0.f, float y = 0.f);
        
    public:
        float Length() const;
        float LengthSquared() const;
        Vector2 Normalized() const;
        float Dot(const Vector2& other) const;
        
    public:
        bool operator==(const Vector2& other) CONST;
        bool operator!=(const Vector2& other) const;
        Vector2& operator=(const Vector2& other);
        
        Vector2 operator+(const Vector2& other) const;
        Vector2& operator+=(const Vector2& other);        
        Vector2 operator-(const Vector2& other) const;
        Vector2& operator-=(const Vector2& other);
        
        Vector2 operator*(const Vector2& other) const;
        Vector2 operator*(float scale) const;
        Vector2& operator*=(const Vector2& other);
        Vector2& operator*=(float scale);

        Vector2 operator/(const Vector2& other) const;
        Vector2 operator/(float scale) const;
        Vector2& operator/=(const Vector2& other);
        Vector2& operator/=(float scale);
        
    public:
        float x = 0.f;
        float y = 0.f;   
        
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 Right;
        static const Vector2 Up;
    };
}