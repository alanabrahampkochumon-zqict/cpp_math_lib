#pragma once

#include <type_traits>

#include "Vector2D.h"
#include "matrix/Matrix3D.h"
#include "matrix/Matrix3D.h"

namespace math
{
    template<typename T>
    struct Vector3D
    {
        using value_type = T;

        static_assert(std::is_arithmetic_v<T>, "Vector3D can only be instantiated with numbers(integer, float, doubles etc.");
        // TODO: Write tests for cross arithmetic ops(float * double)...

        Vector3D();
        Vector3D(T v1, T v2, T v3);
        Vector3D(Vector2D<T> vec, T v);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector3D(const Vector3D<S>& other);


        union {
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T s, t, p; };

            T elements[3];
        };


        T& operator[](int i);
        const T& operator[](int i) const;

        template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator+(const Vector3D<S>& other) const -> Vector3D<std::common_type_t<T, S>>;

        template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector3D& operator+=(const Vector3D<S>& other);
        
    	template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator-(const Vector3D<S>& other) const -> Vector3D<std::common_type_t<T, S>>;

        template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    	Vector3D& operator-=(const Vector3D<S>& other);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator*(const S& scalar) const -> Vector3D<std::common_type_t<T, S>>;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector3D& operator*=(const S& scalar);

        template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator/(const S& scalar) const -> Vector3D<std::common_type_t<T, S>>;

        template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector3D& operator/=(const S& scalar);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto dot(const Vector3D<S>& other) const -> std::common_type_t<T, S>;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto cross(const Vector3D<S>& other) const -> Vector3D<std::common_type_t<T, S>>;

        T mag() const;

        Vector3D normalize() const;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        static auto dot(const Vector3D& vecA, const Vector3D<S>& vecB) -> std::common_type_t<T, S>;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        static auto cross(const Vector3D& vecA, const Vector3D<S>& vecB) -> Vector3D<std::common_type_t<T, S>>;

        // Projection & Rejection
        /**
         * Projects the current vector onto to the `onto` vector.
         * @tparam S Type of the vector to be projected on to (b).
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto project(const Vector3D<S>& onto, bool ontoNormalized = false) const -> Vector3D<std::common_type_t<T, S>>;

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam S Type of the vector to be vector projected onto.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto reject(const Vector3D<S>& onto, bool ontoNormalized = false) const -> Vector3D<std::common_type_t<T, S>>;

        /**
         * Static wrapper for vector projection.
         * @tparam S Type of the vector to be projected to.
         * @param vector Vector to project.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        static auto project(const Vector3D& vector, const Vector3D<S>& onto, bool ontoNormalized = false) -> Vector3D<std::common_type_t<T, S>>;

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam S Type of the vector to be vector projected onto.
         * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        static auto reject(const Vector3D& vector, const Vector3D<S>& onto, bool ontoNormalized = false) -> Vector3D<std::common_type_t<T, S>>;

    };

    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    auto operator*(S scalar, const Vector3D<T>& vector) -> Vector3D<std::common_type_t<T, S>>;

    // Aliases
    using vec3 = Vector3D<float>;
    using dvec3 = Vector3D<double>;

}

#include "Vector3D.tpp"