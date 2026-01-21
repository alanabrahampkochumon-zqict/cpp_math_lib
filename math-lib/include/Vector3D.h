#pragma once

namespace math
{
    struct Vector3D
    {
        Vector3D();
        Vector3D(float v1, float v2, float v3);


        union {
            struct { float x, y, z; };
            struct { float r, g, b; };
            struct { float s, t, p; };

            float elements[3];
        };


        inline float& operator[](int i);
        inline const float& operator[](int i) const;

        inline Vector3D operator+(const Vector3D& another) const;
        inline Vector3D& operator+=(const Vector3D& another);
        inline Vector3D operator-(const Vector3D& another) const;
        inline Vector3D& operator-=(const Vector3D& another);
        inline Vector3D operator*(const float& scalar) const;
        inline Vector3D& operator*=(const float& scalar);
        inline Vector3D operator/(const float& scalar) const;
        inline Vector3D& operator/=(const float& scalar);
         
        inline float mag() const;
        inline Vector3D normalize() const;
        

    };

    inline Vector3D operator*(float scalar, const Vector3D& vector);

    
}

#include "Vector3D.tpp"