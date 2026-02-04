#pragma once

#include <type_traits>

#include "Vector2D.h"
#include "Vector3D.h"

namespace math
{
    template<typename T>
    struct Vector4D
    {
        static_assert(std::is_floating_point_v<T>, "Vector4D can only be instantiated with floats(float and double)");

        Vector4D();
        Vector4D(T v1, T v2, T v3, T v4);
        Vector4D(Vector2D<T> vec1, Vector2D<T> vec2);
        Vector4D(Vector3D<T> vec, T v);


        union {
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            struct { T s, t, p, q; };

            T elements[4];
        };


        T& operator[](int i);
        const T& operator[](int i) const;

        Vector4D operator+(const Vector4D& other) const;
        Vector4D& operator+=(const Vector4D& other);
        Vector4D operator-(const Vector4D& other) const;
        Vector4D& operator-=(const Vector4D& other);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector4D operator*(const S& scalar) const;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector4D& operator*=(const S& scalar);

        template<typename M>
        Vector4D operator/(const M& scalar) const;

        template<typename M>
        Vector4D& operator/=(const M& scalar);

        T dot(const Vector4D& other) const;

        T mag() const;
        Vector4D normalize() const;

        static T dot(const Vector4D& vecA, const Vector4D& vecB);

        // Projection & Rejection
        /**
         * Projects the current vector onto to the `onto` vector.
         * @tparam S Type of the vector to be projected on to (b).
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        Vector4D<T> project(const Vector4D<S>& onto, bool ontoNormalized = false) const;

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam S Type of the vector to be vector projected onto.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        Vector4D<T> reject(const Vector4D<S>& onto, bool ontoNormalized = false) const;

        /**
         * Static wrapper for vector projection.
         * @tparam S Type of the vector to be projected to.
         * @param vector Vector to project.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        static Vector4D project(const Vector4D& vector, const Vector4D<S>& onto, bool ontoNormalized = false);

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam S Type of the vector to be vector projected onto.
         * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        static Vector4D reject(const Vector4D& vector, const Vector4D<S>& onto, bool ontoNormalized = false);

    };

    template<typename T, typename M>
    Vector4D<T> operator*(M scalar, const Vector4D<T>& vector);

    // Aliases
    using vec4 = Vector4D<float>;
    using dvec4 = Vector4D<double>;

}

#include "Vector4D.tpp"