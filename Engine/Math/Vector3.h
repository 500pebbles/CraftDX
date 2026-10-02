#pragma once
#include "Core/Core.h"

namespace Craft
{
    class Vector3
    {
    public:
        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        Vector3(const Vector3& other);
        ~Vector3() = default;
        
    public:
        float Length() const;
        float LengthSquared() const;
        Vector3 Normalized() const;

        float Dot(const Vector3& other) const;
        Vector3 Cross(const Vector3& other) const;
        
    public:
        bool operator==(const Vector3& other) const;
        bool operator!=(const Vector3& other) const;
        Vector3& operator=(const Vector3& other);

        Vector3 operator+(const Vector3& other) const;
        Vector3& operator+=(const Vector3& other);
        Vector3 operator-(const Vector3& other) const;
        Vector3& operator-=(const Vector3& other);
        
        Vector3 operator*(const Vector3& other) const;
        Vector3 operator*(float scale) const;
        Vector3& operator*=(const Vector3& other);
        Vector3& operator*=(float scale);

        Vector3 operator/(const Vector3& other) const;
        Vector3 operator/(float scale) const;
        Vector3& operator/=(const Vector3& other);
        Vector3& operator/=(float scale);

    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 Right;
        static const Vector3 Up;
        static const Vector3 Forward;
    };
}
