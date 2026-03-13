#pragma once
/**
 * @file Vector4D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief Templated 4D Vector supporting integral, floating-point and boolean types.
 * @tparam T Type of Vector4D components. Must satisfy @ref Arithmetic concept.
 *
 * @note Arithmetic operations are limited to numeric types via @ref StrictArithmetic concept.
 *
 * @par Configuration
 * Define `ENABLE_FGM_SHADER_OPERATORS` to enable comparison operators (>, <, etc.).
 * Even if disabled, functional comparisons like `greaterThan()` remain available.
 * Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2D.h"
#include "Vector3D.h"

#include <cstddef>

// TODO:Add NEQ (+ Static) + Initializer of scalar + Vector3D for completion

namespace fgm
{
    template <Arithmetic T>
    struct Vector4D
    {
        using value_type = T;

        static constexpr std::size_t dimension = 4; ///< Vector Dimension

        union {
            struct
            {
                T x; ///< X-axis component
                T y; ///< Y-axis component
                T z; ///< Z-axis component
                T w; ///< W-axis (homogeneous) component
            };
            struct
            {
                T r; ///< Red channel
                T g; ///< Green channel
                T b; ///< Blue channel
                T a; ///< Alpha channel
            };
            struct
            {
                T s; ///< S-coordinate
                T t; ///< T-coordinate
                T p; ///< P-coordinate
                T q; ///< Q-coordinate
            };

            T elements[dimension];
        };




        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/


        /**
         * @brief Initialize @ref Vector4D with zeros.
         */
        Vector4D();


        /**
         * @brief Initialize @ref Vector4D with passed in values.
         * @param[in]  v1 First entry of @ref Vector4D.
         * @param[in]  v2 Second entry of @ref Vector4D.
         * @param[in]  v3 Third entry of @ref Vector4D.
         * @param[in]  v4 Fourth entry of @ref Vector4D.
         */
        Vector4D(T v1, T v2, T v3, T v4);


        /**
         * @brief Initialize @ref Vector4D with 2 @ref Vector2D.
         * @param[in]  vec1 First two entries of @ref Vector4D.
         * @param[in]  vec2 Last two entries of @ref Vector4D.
         */
        Vector4D(Vector2D<T> vec1, Vector2D<T> vec2);


        /**
         * @brief Initialize @ref Vector4D with 1 @ref Vector3D and 1 T value.
         * @param[in]  vec First three entries of @ref Vector4D.
         * @param[in]  v Last entry for @ref Vector4D.
         */
        Vector4D(Vector3D<T> vec, T v);


        /**
         * @brief Initialize @ref Vector4D with 1 T value and 1 @ref Vector3D.
         * @param[in]  vec First three entries of @ref Vector4D.
         * @param[in]  v Last entry for @ref Vector4D.
         */
        Vector4D(T v, Vector3D<T> vec);


        /**
         * @brief Initialize @ref Vector4D from another @ref Vector4D of a different type.
         * @tparam U Numeric type of the source vector.
         * @param[in]  other Source vector to be converted.
         */
        template <Arithmetic U>
        Vector4D(const Vector4D<U>& other);




        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        /**
         * @brief Index-based([]) mutator overload.
         * @param[in]  i Index of the Vector component.
         * @return Reference to the Vector component.
         */
        T& operator[](std::size_t i);

        /**
         * @brief Index-based([]) accessor overload.
         * @param[in]  i Index of the Vector component.
         * @return Immutable reference to the Vector component.
         */
        const T& operator[](std::size_t i) const;




        /***************************************
         *                                     *
         *             EQUALITY                *
         *                                     *
         ***************************************/

        /**
         * @brief Perform equality check for all components.
         * @note For Vector<bool> mask use @ref neq for inequality and @ref eq for equality.
         *
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in]  other Vector being compared against.
         * @param[in]  epsilon Epsilon used for comparison of `std::floating_point` type.
         * @return whether all components of the vector are the same.
         */
        template <Arithmetic U>
        bool allEq(const Vector4D<U>& other,
                   double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON
                                                                                             : FLOAT_EPSILON) const;
        /**
         * @brief Perform equality check for all components.
         * @note For Vector<bool> mask use @ref neq for inequality and @ref eq for equality.
         *
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in]  vecA Vector being compared.
         * @param[in]  vecB Vector being compared against.
         * @param[in]  epsilon Epsilon used for comparison of `std::floating_point` type.
         * @return whether all components of the vector are the same.
         */
        template <Arithmetic U>
        static bool allEq(const Vector4D& vecA, const Vector4D<U>& vecB,
                          double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON
                                                                                                    : FLOAT_EPSILON);

        /**
         * @brief Equality operator overload for Vector comparison.
         * @note For Vector<bool> mask use @ref eq.
         *
         * @tparam U Numeric type of RHS Vector.
         * @param[in] other Vector being compared against (RHS of the operator).
         * @return whether all components of the vector are the same.
         */
        template <Arithmetic U>
        bool operator==(const Vector4D<U>& other) const;


        /**
         * @brief Inequality operator overload for Vector comparison.
         * @note For Vector<bool> mask use @ref neq.
         *
         * @tparam U Numeric type of RHS Vector.
         * @param[in] other Vector being compared against (RHS of the operator).
         * @return whether any component of the Vector differ.
         */
        template <Arithmetic U>
        bool operator!=(const Vector4D<U>& other) const;


        /**
         * @brief Perform component-wise equality check.
         * @note For bool result use @ref allEq or equality operators(==, !=).
         *
         * @tparam U Numeric type of @ref Vector4D being compared against.
         * @param[in] other Vector being compared against.
         * @param[in] epsilon Epsilon used for comparison of `std::floating_point` type.
         * @return Vector mask of whether components are the same.
         */
        template <Arithmetic U>
        Vector4D<bool> eq(const Vector4D<U>& other,
                          double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                              ? DOUBLE_EPSILON
                              : FLOAT_EPSILON) const;

        /**
         * @brief Static wrapper for @ref eq.
         * @note For bool result use `allEq` or equality operators(==, !=).
         *
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] vecA Vector being compared.
         * @param[in] vecB Vector being compared against.
         * @param[in] epsilon Epsilon used for comparison of `std::floating_point` type.
         * @return Vector mask of whether components are the same.
         */
        template <Arithmetic U>
        static Vector4D<bool> eq(const Vector4D& vecA, const Vector4D<U>& vecB,
                                 double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                     ? DOUBLE_EPSILON
                                     : FLOAT_EPSILON);




        /***************************************
         *                                     *
         *            COMPARISONS              *
         *                                     *
         ***************************************/

        /**
         * @brief Perform component-wise greater than comparison.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are larger.
         */
        template <StrictArithmetic U>
        Vector4D<bool> gt(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        /**
         * @brief Static wrapper for @ref gt.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] vecA Vector being compared.
         * @param[in] vecB Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are larger.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> gt(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater than or equal comparison.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are larger or equal.
         */
        template <StrictArithmetic U>
        Vector4D<bool> gte(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        /**
         * @brief Static wrapper for @ref gte.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] vecA Vector being compared.
         * @param[in] vecB Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are larger or equal.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> gte(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less than comparison.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are smaller.
         */
        template <StrictArithmetic U>
        Vector4D<bool> lt(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        /**
         * @brief Static wrapper for @ref lt.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] vecA Vector being compared.
         * @param[in] vecB Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are smaller.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> lt(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less than or equal comparison.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are smaller or equal.
         */
        template <StrictArithmetic U>
        Vector4D<bool> lte(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        /**
         * @brief Static wrapper for @ref lte.
         * @tparam U Numeric type of the @ref Vector4D being compared against.
         * @param[in] vecA Vector being compared.
         * @param[in] vecB Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are smaller or equal.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> lte(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;

#ifdef ENABLE_FGM_SHADER_OPERATORS

        /**
         * @brief Greater than operator overload for Vector Comparison.
         * @note Operator overloads for comparison are not included by default. Define `ENABLE_FGM_SHADER_OPERATORS` to
         * use them.
         *
         * @tparam U Numeric type of RHS Vector.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are larger.
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator>(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @brief Greater than or equal operator overload for Vector Comparison.
         * @note Operator overloads for comparison are not included by default. Define `ENABLE_FGM_SHADER_OPERATORS` to
         * use them.
         *
         * @tparam U Numeric type of RHS Vector.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are larger or equal.
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator>=(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @brief Less than operator overload for Vector Comparison.
         * @note Operator overloads for comparison are not included by default. Define `ENABLE_FGM_SHADER_OPERATORS` to
         * use them.
         *
         * @tparam U Numeric type of RHS Vector.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are smaller.
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator<(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @brief Less than or equal operator overload for Vector Comparison.
         * @note Operator overloads for comparison are not included by default. Define `ENABLE_FGM_SHADER_OPERATORS` to
         * use them.
         *
         * @tparam U Numeric type of RHS Vector.
         * @param[in] other Vector being compared against.
         * @return Vector mask of whether the compared Vector's components are smaller or equal.
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator<=(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;
#endif




        /***************************************
         *                                     *
         *      BOOLEAN BITWISE OPERATORS      *
         *                                     *
         ***************************************/

        /**
         * @brief Perform component-wise Bitwise AND operation.
         * @note Only available for @ref bVec4 and Vectors with `bool` value type.
         *
         * @param[in]  other Vector being compared against.
         * @return Vector mask of whether both Vector components are `true`.
         */
        Vector4D<bool> operator&(const Vector4D<bool>& other) const
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise Bitwise OR operation.
         * @note Only available for @ref bVec4 and Vectors with `bool` value type.
         *
         * @param[in]  other Vector being compared against.
         * @return Vector mask of whether any of the Vector components are `true`.
         */
        Vector4D<bool> operator|(const Vector4D<bool>& other) const
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise Bitwise NOT operation.
         * @note Only available for @ref bVec4 and Vectors with `bool` value type.
         *
         * @return Vector with values inverted (true -> false).
         */
        Vector4D<bool> operator!() const
            requires std::is_same_v<T, bool>;




        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/

        /**
         * @brief Perform component-wise addition.
         * @note Promotes the result to the @ref std::common_type_t of T and U.
         * @note Operation not available for `bool`.
         *
         * @tparam U Numeric type of RHS.
         * @param[in]  other Vector being added.
         * @return Sum of two vectors.
         */
        template <StrictArithmetic U>
        auto operator+(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise addition on the calling vector.
         * @note Operation not available for `bool`.
         *
         * @tparam U Numeric type of RHS.
         * @param[in]  other Vector being added.
         * @return Reference to this vector.
         */
        template <StrictArithmetic U>
        Vector4D& operator+=(const Vector4D<U>& other)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise subtraction.
         * @note Promotes the result to the @ref std::common_type_t of T and U.
         * @note Operation not available for `bool`.
         *
         * @tparam U Numeric type of RHS.
         * @param[in]  other Vector being subtracted.
         * @return Difference between two vectors.
         */
        template <StrictArithmetic U>
        auto operator-(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise subtraction on the calling vector.
         * @note Operation not available for `bool`.
         *
         * @tparam U Numeric type of RHS.
         * @param[in]  other Vector being subtracted.
         * @return Reference to this vector.
         */
        template <StrictArithmetic U>
        Vector4D& operator-=(const Vector4D<U>& other)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise multiplication with a scalar.
         * @note Promotes the result to the @ref std::common_type_t of T and U.
         * @note Operation not available for `bool`.
         *
         * @tparam S Numeric type of scalar.
         * @param[in]  scalar Value to scale by.
         * @return Scaled Vector.
         */
        template <StrictArithmetic S>
        auto operator*(S scalar) const -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise multiplication with a scalar.
         * @note Operation not available for `bool`.
         *
         * @tparam S Numeric type of scalar.
         * @param[in]  scalar Value to scale by.
         * @return Reference to this vector.
         */
        template <StrictArithmetic S>
        Vector4D& operator*=(S scalar)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise division with a scalar.
         * @note Promotes the result to the @ref std::common_type_t of T and U.
         * @note Operation not available for `bool`.
         *
         * @tparam S Numeric type of scalar.
         * @param[in]  scalar Value to scale by.
         * @return Scaled vector.
         */
        template <StrictArithmetic S>
        auto operator/(S scalar) const -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise division with a scalar.
         * @note Promotes the result to the @ref std::common_type_t of T and U.
         * @note Operation not available for `bool`.
         *
         * @tparam S Numeric type of scalar.
         * @param[in]  scalar Value to scale by.
         * @return Reference to this vector.
         */
        template <StrictArithmetic S>
        Vector4D& operator/=(S scalar)
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *        VECTOR DOT PRODUCT         *
         *                                   *
         *************************************/

        /**
         * @brief Compute dot product of two vectors.
         * @note Promotes the result to the @ref std::common_type_t of T and U.
         * @note Operation not available for `bool`.
         *
         * @tparam U Numeric type of the other vector.
         * @param[in]  other Vector to perform dot with.
         * @return scalar dot product.
         */
        template <StrictArithmetic U>
        auto dot(const Vector4D<U>& other) const -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;

        /**
         * @brief Static wrapper for @ref dot.
         * @note Promotes the result to the @ref std::common_type_t of T and U.
         * @note Operation not available for `bool`.
         *
         * @tparam U Numeric type of the other vector.
         * @param[in]  vecA First vector to perform dot product on.
         * @param[in]  vecB The other vector to perform dot product on.
         * @return scalar dot product.
         */
        template <StrictArithmetic U>
        static auto dot(const Vector4D& vecA, const Vector4D<U>& vecB) -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *         VECTOR MAGNITUDE          *
         *                                   *
         *************************************/

        /**
         * @brief Compute the magnitude (length) of this vector.
         * @note Due to difficulty producing an accurate magnitude of `std::integral_vector`, the return type will be of
         * `std::floating_point`.
         * @see @ref Magnitude for details.
         *
         * @return Scalar magnitude.
         */
        Magnitude<T> mag() const
            requires StrictArithmetic<T>;

        /**
         * @brief Static wrapper for @ref mag.
         * @note Due to difficulty producing an accurate magnitude of `std::integral_vector`, the return type will be of
         * `std::floating_point`.
         * @see @ref Magnitude for details.
         *
         * @param[in] vec Vector to compute the magnitude of.
         * @return Scalar magnitude.
         */
        static Magnitude<T> mag(const Vector4D& vec)
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *       VECTOR NORMALIZATION        *
         *                                   *
         *************************************/

        /**
         * @brief Computes the normalized form of this vector.
         * @note Due to difficulty performing normalization of `std::integral_vector`, the return type will be of
         * `std::floating_point`.
         * @see @ref Magnitude for details.
         *
         * @return Unit vector.
         */
        Vector4D<Magnitude<T>> normalize() const
            requires StrictArithmetic<T>;

        /**
         * @brief Static wrapper for @ref normalize.
         * @note Due to difficulty performing normalization of `std::integral_vector`, the return type will be of
         * `std::floating_point`.
         * @see @ref Magnitude for details.
         *
         * @return Unit vector.
         */
        static Vector4D<Magnitude<T>> normalize(const Vector4D& vec)
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *        VECTOR PROJECTION          *
         *                                   *
         *************************************/

        /**
         * Project the current vector onto another vector.
         * @tparam U Numeric type of vector being projected onto.
         * @param[in] onto Vector to be projected onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * is projected onto is normalized.
         * @return Projected vector.
         */
        template <StrictArithmetic U>
        auto project(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;

        /**
         * Static wrapper for @ref project.
         * @tparam U Numeric type of vector being projected onto.
         * @param[in] vector Vector to be projected.
         * @param[in] onto Vector to be projected onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * is projected onto is normalized.
         * @return Projected vector.
         */
        template <StrictArithmetic U>
        static auto project(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false)
            -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *         VECTOR REJECTION          *
         *                                   *
         *************************************/

        /**
         * Reject the current vector onto another vector.
         * @tparam U Numeric type of vector being rejected onto.
         * @param[in] onto Vector to be rejected onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * is rejected onto is normalized.
         * @return Rejected vector.
         */
        template <StrictArithmetic U>
        auto reject(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * Static wrapper for @ref reject.
         * @tparam U Numeric type of vector being rejected onto.
         * @param[in] vector Vector being projected.
         * @param[in] onto Vector to be projected onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * is projected onto is normalized.
         * @return Rejected vector.
         */
        template <StrictArithmetic U>
        static auto reject(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false)
            -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;
    };




    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/

    /**
     * @brief Perform component-wise multiplication with a scalar.
     * @note Promotes the result to the @ref std::common_type_t of T and U.
     * @note Operation not available for `bool`.
     *
     * @tparam S Numeric type of scalar.
     * @param[in]  scalar Value to scale by.
     * @param[in]  vector Vector to scale[RHS].
     * @return Scaled Vector.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    auto operator*(S scalar, const Vector4D<T>& vector) -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>;




    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/
    using bVec4 = Vector4D<bool>;                ///< bool vector
    using iVec4 = Vector4D<int>;                 ///< int vector
    using uVec4 = Vector4D<unsigned int>;        ///< unsigned int vector
    using vec4 = Vector4D<float>;                ///< float vector
    using lVec4 = Vector4D<long long>;           ///< long long vector
    using dVec4 = Vector4D<double>;              ///< double vector
    using ulVec4 = Vector4D<unsigned long long>; ///< unsigned long long vector

} // namespace fgm


#include "Vector4D.tpp"