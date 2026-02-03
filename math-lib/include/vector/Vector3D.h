#pragma once

#include <type_traits>

#include "Vector2D.h"

namespace math
{
    template<typename T>
    struct Vector3D
    {
        static_assert(std::is_floating_point_v<T>, "Vector3D can only be instantiated with floats(float and double)");

        Vector3D();
        Vector3D(T v1, T v2, T v3);
        Vector3D(Vector2D<T> vec, T v);


        union {
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T s, t, p; };

            T elements[3];
        };


        T& operator[](int i);
        const T& operator[](int i) const;

        Vector3D operator+(const Vector3D& other) const;
        Vector3D& operator+=(const Vector3D& other);
        Vector3D operator-(const Vector3D& other) const;
        Vector3D& operator-=(const Vector3D& other);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector3D operator*(const S& scalar) const;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector3D& operator*=(const S& scalar);

        template<typename M>
        Vector3D operator/(const M& scalar) const;

        template<typename M>
        Vector3D& operator/=(const M& scalar);

        T dot(const Vector3D& other) const;
        Vector3D cross(const Vector3D& other) const;

        T mag() const;
        Vector3D normalize() const;

        static T dot(const Vector3D& vecA, const Vector3D& vecB);
        static Vector3D cross(const Vector3D& vecA, const Vector3D& vecB);

        // Projection & Rejection
        /**
         * Projects the current vector onto to the `onto` vector.
         * @tparam S Type of the vector to be projected on to (b).
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        Vector3D<T> project(const Vector3D<S>& onto, bool ontoNormalized = false) const;

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam S Type of the vector to be vector projected onto.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        Vector3D<T> reject(const Vector3D<S>& onto, bool ontoNormalized = false) const;

        /**
         * Static wrapper for vector projection.
         * @tparam S Type of the vector to be projected to.
         * @param vector Vector to project.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        static Vector3D project(const Vector3D& vector, const Vector3D<S>& onto, bool ontoNormalized = false);

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam S Type of the vector to be vector projected onto.
         * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<typename S>
        static Vector3D reject(const Vector3D& vector, const Vector3D<S>& onto, bool ontoNormalized = false);

    };

    template<typename T, typename M>
    Vector3D<T> operator*(M scalar, const Vector3D<T>& vector);

    // Aliases
    using vec3 = Vector3D<float>;
    using dvec3 = Vector3D<double>;

}

#include "Vector3D.tpp"