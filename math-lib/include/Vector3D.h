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


        float& operator[](int i);
        const float& operator[](int i) const;

        Vector3D operator+(const Vector3D& another) const;
        Vector3D operator-(const Vector3D& another) const;
        Vector3D operator*(const float& scalar) const;
        Vector3D& operator*=(const float& scalar);
        Vector3D operator/(const float& scalar) const;
        Vector3D& operator/=(const float& scalar);

        float mag() const;
        
    };

    inline Vector3D operator*(float scalar, const Vector3D& vector);
    //inline Vector3D operator/(float scalar, const Vector3D& vector);

    // Helper Functions
    inline Vector3D _times(const Vector3D& vec, const float scalar);

    
}

#include "Vector3D.tpp"