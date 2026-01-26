#pragma once

#include <type_traits>

namespace math
{
    template<typename T>
    struct Vector4D
    {
        static_assert(std::is_floating_point_v<T>, "Vector4D can only be instantiated with floats(floats, and numbers)");

        Vector4D();
        Vector4D(T v1, T v2, T v3);


        union {
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T s, t, p; };

            T elements[3];
        };


        T& operator[](int i);
        const T& operator[](int i) const;

        Vector4D operator+(const Vector4D& other) const;
        Vector4D& operator+=(const Vector4D& other);
        Vector4D operator-(const Vector4D& other) const;
        Vector4D& operator-=(const Vector4D& other);

        template<typename M>
        Vector4D operator*(const M& scalar) const;

        template<typename M>
        Vector4D& operator*=(const M& scalar);

        template<typename M>
        Vector4D operator/(const M& scalar) const;

        template<typename M>
        Vector4D& operator/=(const M& scalar);

        T dot(const Vector4D& other) const;
        Vector4D cross(const Vector4D& other) const;

        T mag() const;
        Vector4D normalize() const;

        static T dot(const Vector4D& vecA, const Vector4D& vecB);
        static Vector4D cross(const Vector4D& vecA, const Vector4D& vecB);

    };

    template<typename T, typename M>
    Vector4D<T> operator*(M scalar, const Vector4D<T>& vector);

    // Aliases
    using vec4 = Vector4D<float>;
    using dvec4 = Vector4D<double>;

}

#include "Vector4D.tpp"