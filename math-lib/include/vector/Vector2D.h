#pragma once

#include <type_traits>

namespace math
{
    template <typename T>
    struct Vector2D
    {
        static_assert(std::is_floating_point_v<T>, "Vector2D can only be instantiated with floats(float and double)");

        Vector2D();
        Vector2D(T v1, T v2);

        union
        {
            struct
            {
                T x, y;
            };
            struct
            {
                T r, g;
            };
            struct
            {
                T s, t;
            };
            T elements[2];
        };

        T &operator[](int i);
        const T &operator[](int i) const;

        Vector2D operator+(const Vector2D &other) const;
        Vector2D &operator+=(const Vector2D &other);
        Vector2D operator-(const Vector2D &other) const;
        Vector2D &operator-=(const Vector2D &other);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector2D operator*(const S &scalar) const;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector2D &operator*=(const S &scalar);

        template <typename S>
        Vector2D operator/(const S &scalar) const;

        template <typename M>
        Vector2D &operator/=(const M &scalar);

        T dot(const Vector2D &other) const;
        T cross(const Vector2D &other) const;

        T mag() const;
        Vector2D normalize() const;

        // Projection & Rejection
        template<typename S>
        Vector2D<T> project(const Vector2D<S>& onto) const;


        static T dot(const Vector2D &vecA, const Vector2D &vecB);
        static T cross(const Vector2D &vecA, const Vector2D &vecB);

        // TODO: Refactor with enable_if_t for S

        /**
         * Static wrapper for vector projection.
         * @tparam S Type of the vector to be projected to
         * @param vector Vector to project.
         * @param onto Vector to be projected onto.
         * @return Projected vector.
         */
        template<typename S>
        static Vector2D<S> project(const Vector2D& vector, const Vector2D<S>& onto);
    };

    template <typename T, typename S>
    Vector2D<T> operator*(S scalar, const Vector2D<T> &vector);

    using vec2 = Vector2D<float>;
    using dvec2 = Vector2D<double>;
}

#include "Vector2D.tpp"