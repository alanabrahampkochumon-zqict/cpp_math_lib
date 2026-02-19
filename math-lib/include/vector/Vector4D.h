#pragma once

#include "Vector2D.h"
#include "Vector3D.h"

#include <cstddef>

namespace math
{
    template<Arithmetic T>
    struct Vector4D
    {
        using value_type = T;

        static constexpr std::size_t dimension = 4;

        union {
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            struct { T s, t, p, q; };

            T elements[dimension];
        };

        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/

        Vector4D();
        Vector4D(T v1, T v2, T v3, T v4);
        Vector4D(Vector2D<T> vec1, Vector2D<T> vec2);
        Vector4D(Vector3D<T> vec, T v);

        
        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        T& operator[](std::size_t i);
        const T& operator[](std::size_t i) const;


        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/

        Vector4D operator+(const Vector4D& other) const;
        Vector4D& operator+=(const Vector4D& other);
        Vector4D operator-(const Vector4D& other) const;
        Vector4D& operator-=(const Vector4D& other);

        template <Arithmetic S>
        Vector4D operator*(const S& scalar) const;

        template <Arithmetic S>
        Vector4D& operator*=(const S& scalar);

        template<Arithmetic S>
        Vector4D operator/(const S& scalar) const;

        template<Arithmetic S>
        Vector4D& operator/=(const S& scalar);

        /*************************************
         *                                   *
         *        VECTOR DOT PRODUCT         *
         *                                   *
         *************************************/
        T dot(const Vector4D& other) const;
        static T dot(const Vector4D& vecA, const Vector4D& vecB);

        /*************************************
         *                                   *
         *         VECTOR MAGNITUDE          *
         *                                   *
         *************************************/
        T mag() const;

        /*************************************
         *                                   *
         *       VECTOR NORMALIZATION        *
         *                                   *
         *************************************/
        Vector4D normalize() const;


        /*************************************
         *                                   *
         *        VECTOR PROJECTION          *
         *                                   *
         *************************************/
        /**
         * Projects the current vector onto to the `onto` vector.
         * @tparam U Type of the vector to be projected on to (b).
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<Arithmetic U>
        Vector4D<T> project(const Vector4D<U>& onto, bool ontoNormalized = false) const;

        /**
		 * Static wrapper for vector projection.
		 * @tparam U Type of the vector to be projected to.
		 * @param vector Vector to project.
		 * @param onto Vector to be projected onto.
		 * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		 * @return Projected vector.
		 */
        template<Arithmetic U>
        static Vector4D project(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false);

    	
    	/*************************************
         *                                   *
         *         VECTOR REJECTION          *
         *                                   *
         *************************************/

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam U Type of the vector to be vector projected onto.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<Arithmetic U>
        Vector4D<T> reject(const Vector4D<U>& onto, bool ontoNormalized = false) const;


        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam U Type of the vector to be vector projected onto.
         * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
         * @return Projected vector.
         */
        template<Arithmetic U>
        static Vector4D reject(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false);

    };


    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/
    template<Arithmetic T, Arithmetic S>
    Vector4D<T> operator*(S scalar, const Vector4D<T>& vector);


    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/
    using vec4 = Vector4D<float>;
    using dvec4 = Vector4D<double>;

}

#include "Vector4D.tpp"