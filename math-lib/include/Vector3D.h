#pragma once

#include <type_traits>

namespace math
{
	template<typename T>
    struct Vector3D
    {
        static_assert(std::is_floating_point_v<T>, "Vector3D can only be instantiated with floats(floats, and numbers)");

        Vector3D();
        Vector3D(T v1, T v2, T v3);


        union {
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T s, t, p; };

            T elements[3];
        };


        T& operator[](int i);
        const T& operator[](int i) const;

        Vector3D operator+(const Vector3D& another) const;
        Vector3D& operator+=(const Vector3D& another);
        Vector3D operator-(const Vector3D& another) const;
        Vector3D& operator-=(const Vector3D& another);
		template<typename M>
        Vector3D operator*(const M& scalar) const;
        template<typename M>
        Vector3D& operator*=(const M& scalar);
        template<typename M>
        Vector3D operator/(const M& scalar) const;
        template<typename M>
        Vector3D& operator/=(const M& scalar);
         
        T mag() const;
        Vector3D normalize() const;
        

    };

    template<typename T, typename M>
    Vector3D<T> operator*(M scalar, const Vector3D<T>& vector);

    
}

#include "Vector3D.tpp"