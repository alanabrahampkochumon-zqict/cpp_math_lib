#pragma once

#include <type_traits>

namespace math
{
    template<typename T>
    struct Vector2D
    {
        static_assert(std::is_floating_point_v<T>, "Vector2D can only be instantiated with floats(floats, and numbers)");

        Vector2D();
        Vector2D(T v1, T v2);


        union {
            struct { T x, y; };
            struct { T r, g; };
            struct { T s, t; };
            T elements[2];
        };


        T& operator[](int i);
        const T& operator[](int i) const;

        Vector2D operator+(const Vector2D& other) const;
        Vector2D& operator+=(const Vector2D& other);
        Vector2D operator-(const Vector2D& other) const;
        Vector2D& operator-=(const Vector2D& other);

        template<typename M>
        Vector2D operator*(const M& scalar) const;

        template<typename M>
        Vector2D& operator*=(const M& scalar);

        template<typename M>
        Vector2D operator/(const M& scalar) const;

        template<typename M>
        Vector2D& operator/=(const M& scalar);

        T dot(const Vector2D& other) const;
        T cross(const Vector2D& other) const;

        T mag() const;
        Vector2D normalize() const;

        static T dot(const Vector2D& vecA, const Vector2D& vecB);
        static T cross(const Vector2D& vecA, const Vector2D& vecB);

    };

    using vec2 = Vector2D<float>;
    using dvec2 = Vector2D<double>;

    template<typename T, typename M>
    Vector2D<T> operator*(M scalar, const Vector2D<T>& vector);

}

#include "Vector2D.tpp"