#include "Vector2.h"
#include "cmath"
#include "cassert"
#include "MathDefines.h"

namespace Craft
{
    const Vector2 Vector2::Zero(0.f, 0.f);
    const Vector2 Vector2::One(1.f, 1.f);
    const Vector2 Vector2::Right(1.f, 0.f);
    const Vector2 Vector2::Up(0.f, 1.f);
    
    Vector2::Vector2(float x, float y)
        : x(x), y(y)
    {
    }

    float Vector2::Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    float Vector2::LengthSquared() const
    {
        return x * x + y * y;
    }

    Vector2 Vector2::Normalized() const
    {
        float length = Length();
        if (length <= KindaSmallNumber) return Vector2::Zero;
    
        return Vector2(x / length, y / length);
    }

    float Vector2::Dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    bool Vector2::operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }

    Vector2& Vector2::operator=(const Vector2& other)
    {
        x = other.x;
        y = other.y;
        
        return *this;
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2& Vector2::operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2& Vector2::operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    Vector2 Vector2::operator*(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 Vector2::operator*(float scale) const
    {
        return Vector2(x * scale, y * scale);
    }

    Vector2& Vector2::operator*=(const Vector2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2& Vector2::operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    Vector2 Vector2::operator/(const Vector2& other) const
    {
        if (std::abs(other.x) <= KindaSmallNumber
            || std::abs(other.y) <= KindaSmallNumber)
        {
            assert(false && "other.x and other.y should not be near 0");
            return Vector2::Zero;
        }
        return Vector2(x / other.x, y / other.y);
    }

    Vector2 Vector2::operator/(float scale) const
    {
        if (std::abs(scale) <= KindaSmallNumber)
        {
            assert(false && "scale should not be near 0");
            return Vector2::Zero;
        }
        return Vector2(x / scale, y / scale);
    }

    Vector2& Vector2::operator/=(const Vector2& other)
    {
        if (std::abs(other.x) <= KindaSmallNumber || std::abs(other.y) <= KindaSmallNumber)
        {
            assert(false && "other.x and other.y should not be near 0");
            return *this;
        }
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2& Vector2::operator/=(float scale)
    {
        if (std::abs(scale) <= KindaSmallNumber)
        {
            assert(false && "scale should not be near 0");
            return *this;
        }
        x /= scale;
        y /= scale;
        return *this;
    }
}
