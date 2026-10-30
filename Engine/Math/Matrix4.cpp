#include "Matrix4.h"

#include <cstring>
#include <filesystem>
#include <utility>

#include "MathDefines.h"

namespace Craft
{
    const Matrix4 Matrix4::Identity = Matrix4();    
    
    Matrix4::Matrix4()
    {
        // 새로 생성하는 Matrix4는 기본적으로 단위 행렬
        memset(elements, 0, sizeof(elements));
        m00 = m11 = m22 = m33 = 1.0f;
    }

    Matrix4::Matrix4(const Matrix4& other)
    {
        memcpy(elements, other.elements, sizeof(elements));
    }
    
    Matrix4 Matrix4::Transpose(const Matrix4& matrix)
    {
        Matrix4 m = matrix;
        std::swap(m.m01, m.m10);
        std::swap(m.m02, m.m20);
        std::swap(m.m03, m.m30);
        std::swap(m.m12, m.m21);
        std::swap(m.m13, m.m31);
        std::swap(m.m23, m.m32);
        
        return m;
    }

    Matrix4 Matrix4::InverseRotation(const Matrix4& matrix)
    {
        return Transpose(matrix);
    }

    Matrix4 Matrix4::Scale(float x, float y, float z)
    {
        Matrix4 m;
        m.m00 = x;		m.m01 = 0.0f; m.m02 = 0.0f;	m.m03 = 0.0f;
        m.m10 = 0.0f;	m.m11 = y;	  m.m12 = 0.0f;	m.m13 = 0.0f;
        m.m20 = 0.0f;	m.m21 = 0.0f; m.m22 = z;	m.m23 = 0.0f;
        m.m30 = 0.0f;	m.m31 = 0.0f; m.m32 = 0.0f;	m.m33 = 1.0f;

        return m;
    }

    Matrix4 Matrix4::Scale(const Vector3& scale)
    {                       
        return Scale(scale.x, scale.y, scale.z);
    }

    Matrix4 Matrix4::Scale(float scale)
    {
        return Scale(scale, scale, scale);
    }

    Matrix4 Matrix4::RotationX(float angle)
    {
        float cos = std::cos(angle * DegreesToRadians);
        float sin = std::sin(angle * DegreesToRadians);
        
        Matrix4 m;
        m.m00 = 1.0f;	m.m01 = 0.0f; m.m02 = 0.0f;	m.m03 = 0.0f;
        m.m10 = 0.0f;	m.m11 =  cos; m.m12 =  sin;	m.m13 = 0.0f;
        m.m20 = 0.0f;	m.m21 = -sin; m.m22 =  cos;	m.m23 = 0.0f;
        m.m30 = 0.0f;	m.m31 = 0.0f; m.m32 = 0.0f;	m.m33 = 1.0f;
        
        return m;
    }

    Matrix4 Matrix4::RotationY(float angle)
    {
        float cos = std::cos(angle * DegreesToRadians);
        float sin = std::sin(angle * DegreesToRadians);
        
        Matrix4 m;
        m.m00 =  cos;	m.m01 = 0.0f; m.m02 = -sin;	m.m03 = 0.0f;
        m.m10 = 0.0f;	m.m11 = 1.0f; m.m12 = 0.0f;	m.m13 = 0.0f;
        m.m20 =  sin;	m.m21 = 0.0f; m.m22 =  cos;	m.m23 = 0.0f;
        m.m30 = 0.0f;	m.m31 = 0.0f; m.m32 = 0.0f;	m.m33 = 1.0f;
        
        return m;
    }

    Matrix4 Matrix4::RotationZ(float angle)
    {
        float cos = std::cos(angle * DegreesToRadians);
        float sin = std::sin(angle * DegreesToRadians);
        
        Matrix4 m;
        m.m00 =  cos;	m.m01 =  sin; m.m02 = 0.0f;	m.m03 = 0.0f;
        m.m10 = -sin;	m.m11 =  cos; m.m12 = 0.0f;	m.m13 = 0.0f;
        m.m20 = 0.0f;	m.m21 = 0.0f; m.m22 = 1.0f;	m.m23 = 0.0f;
        m.m30 = 0.0f;	m.m31 = 0.0f; m.m32 = 0.0f;	m.m33 = 1.0f;
        
        return m;
    }

    Matrix4 Matrix4::Rotation(float x, float y, float z)
    {
        return RotationX(x) * RotationY(y) * RotationZ(z);
    }

    Matrix4 Matrix4::Rotation(const Vector3& rotation)
    {
        return Rotation(rotation.x, rotation.y, rotation.z);
    }

    Matrix4 Matrix4::Translation(float x, float y, float z)
    {
        Matrix4 m;
        m.m00 = 1.0f;	m.m01 = 0.0f; m.m02 = 0.0f;	m.m03 = 0.0f;
        m.m10 = 0.0f;	m.m11 = 1.0f; m.m12 = 0.0f;	m.m13 = 0.0f;
        m.m20 = 0.0f;	m.m21 = 0.0f; m.m22 = 1.0f;	m.m23 = 0.0f;
        m.m30 = x;  	m.m31 = y;    m.m32 = z;   	m.m33 = 1.0f;
        
        return m;
    }

    Matrix4 Matrix4::Translation(const Vector3& translation)
    {
        return Translation(translation.x, translation.y, translation.z);
    }

    Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& upVector)
    {
        Matrix4 m;
        
        // Setup Forward, Right, Up Vectors.
        Vector3 forward = target - eye;
        assert(forward.Length() > KindaSmallNumber);
        forward = forward.Normalized();
        
        Vector3 right = upVector.Normalized().Cross(forward);
        assert(right.Length() > KindaSmallNumber);
        right = right.Normalized();
        
        Vector3 up = forward.Cross(right).Normalized();
        
        // Setup Location values.
        float x = -eye.Dot(right);
        float y = -eye.Dot(up);
        float z = -eye.Dot(forward);
        
        // View Matrix. 
        m.m00 = right.x;   m.m01 = up.x;   m.m02 = forward.x;   m.m03 = 0.0f;
        m.m10 = right.y;   m.m11 = up.y;   m.m12 = forward.y;   m.m13 = 0.0f;
        m.m20 = right.z;   m.m21 = up.z;   m.m22 = forward.z;   m.m23 = 0.0f;
        m.m20 = right.z;   m.m21 = up.z;   m.m22 = forward.z;   m.m23 = 0.0f;
        m.m30 = x;         m.m31 = y;      m.m32 = z;           m.m33 = 1.0f;
        
        return m;
    }

    Matrix4 Matrix4::Perspective(float fieldOfView, float width, float height, float nearDistance, float farDistance)
    {   
        assert(fieldOfView > 0.f && fieldOfView < 180.f);
        assert(width > 0.f && height > 0.f);
        assert(nearDistance > 0.f && farDistance > nearDistance);
        
        float aspect = width / height;
        float d = 1.f / std::tan(fieldOfView * 0.5f * DegreesToRadians); // Focal Length.
        float sy = d;
        float sx = sy / aspect;
        
        float a = farDistance / (farDistance - nearDistance);
        float b = -nearDistance * a;        
        Matrix4 m;
        m.m00 = sx;	m.m01 = 0.0f; m.m02 = 0.0f;	m.m03 = 0.0f;
        m.m10 = 0.0f;	m.m11 = sy; m.m12 = 0.0f;	m.m13 = 0.0f;
        m.m20 = 0.0f;	m.m21 = 0.0f; m.m22 = a;	m.m23 = 1.0f;
        m.m30 = 0.0f;	m.m31 = 0.0f; m.m32 = b;	m.m33 = 0.0f;
        return m;
    }

    Matrix4 Matrix4::InverseTranslationRotation(const Vector3& position, const Vector3& rotation)
    {
        // 역변환 행렬 구하기.
        return Translation(position * -1.0f) * InverseRotation(Rotation(rotation));
    }

    Matrix4& Matrix4::operator=(const Matrix4& other)
    {
        memcpy(elements, other.elements, sizeof(elements));
        return *this;
    }

    Matrix4 Matrix4::operator*(const Matrix4& other) const
    {
        Matrix4 m;

        m.m00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
        m.m01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
        m.m02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
        m.m03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;

        m.m10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
        m.m11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
        m.m12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
        m.m13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;

        m.m20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
        m.m21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
        m.m22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
        m.m23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;

        m.m30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;
        m.m31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
        m.m32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
        m.m33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

        return m;
    }

    Matrix4& Matrix4::operator*=(const Matrix4& other)
    {
        *this = *this * other;
        return *this;
    }

    Vector3 operator*(const Vector3& vector, const Matrix4& matrix)
    {
        // 동차좌표계를 추가하고 4차원벡터 x 행렬곱
        Vector3 v;
        v.x = vector.x * matrix.m00 + vector.y * matrix.m10 + vector.z * matrix.m20 + matrix.m30;
        v.y = vector.x * matrix.m01 + vector.y * matrix.m11 + vector.z * matrix.m21 + matrix.m31;
        v.z = vector.x * matrix.m02 + vector.y * matrix.m12 + vector.z * matrix.m22 + matrix.m32;

        return v;
    }


}
