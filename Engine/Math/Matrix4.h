#pragma once

#include "Math/Vector3.h"

namespace Craft
{
    class Matrix4
    {
    public:
        Matrix4();
        Matrix4(const Matrix4& other);
        ~Matrix4() = default;        
        
    public:
        static Matrix4 Transpose(const Matrix4& matrix); // 전치 함수(행<->열 전환)
        static Matrix4 InverseRotation(const Matrix4& matrix ); // 진짜 역행렬은 복잡. 기저축이 직교(90)일 때만 처리하는, 전치 동작을 역행렬로 구현
        
        static Matrix4 Scale(float x, float y, float z);
        static Matrix4 Scale(const Vector3& scale);
        static Matrix4 Scale(float scale);        
        
        static Matrix4 RotationX(float angle);
        static Matrix4 RotationY(float angle);
        static Matrix4 RotationZ(float angle);
        static Matrix4 Rotation(float x, float y, float z);
        static Matrix4 Rotation(const Vector3& rotation);
        static Matrix4 Translation(float x, float y, float z);
        static Matrix4 Translation(const Vector3& translation);
        
    public:
        const float* Data() const { return elements; }
        
    public:        
        Matrix4& operator=(const Matrix4& other);
        Matrix4 operator*(const Matrix4& other) const;
        Matrix4& operator*=(const Matrix4& other);
        
        friend Vector3 operator*(const Vector3& vector, const Matrix4& matrix);
        
    public:
        static const Matrix4 Identity;
        
        
        
    private:
        /* 공용체에서 메모리를 확보하는 공식
         * 존재하는 변수들을 전부 확인하고 메모리를 가장 크게 사용하는 타입만큼 확보하고 돌려 씀
         * 과거에는 다른 목적으로 공용체를 사용하기도 했지만, 현재는 위를 유일한 목적으로 사용함. */
        union
        {
            struct
            {
                float m00, m01, m02, m03;
                float m10, m11, m12, m13;
                float m20, m21, m22, m23;
                float m30, m31, m32, m33;
            };
            
            float elements[4 * 4];
        };
    };
}

