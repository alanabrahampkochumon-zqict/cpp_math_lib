#pragma once

#include <type_traits>
#include "../MathTraits.h"

namespace math
{
	template <typename T>
	struct Vector2D
	{
		static_assert(std::is_arithmetic_v<T>, "Vector2D can only be instantiated with numbers like floats, integers, etc.");

		using value_type = T;

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

		Vector2D();
		Vector2D(T v1, T v2);


		T& operator[](int i);
		const T& operator[](int i) const;

		template<typename S>
		auto operator+(const Vector2D<S>& other) const
			-> Vector2D<std::common_type_t<S, T>>
			requires std::is_arithmetic_v<S>;

		Vector2D& operator+=(const Vector2D& other);
		Vector2D operator-(const Vector2D& other) const;
		Vector2D& operator-=(const Vector2D& other);

		template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Vector2D operator*(const S& scalar) const;

		template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Vector2D& operator*=(const S& scalar);

		template <typename S>
		Vector2D operator/(const S& scalar) const;

		template <typename M>
		Vector2D& operator/=(const M& scalar);

		T dot(const Vector2D& other) const;
		T cross(const Vector2D& other) const;

		T mag() const;
		Vector2D normalize() const;

		// Projection & Rejection
		/**
		 * Projects the current vector onto to the `onto` vector.
		 * @tparam S Type of the vector to be projected on to (b).
		 * @param onto Vector to be projected onto.
		 * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		 * @return Projected vector.
		 */
		template<typename S>
		Vector2D project(const Vector2D<S>& onto, bool ontoNormalized = false) const;

		/**
		 * Returns the perpendicular component for the current vector after projection to the `onto` vector.
		 * @tparam S Type of the vector to be vector projected onto.
		 * @param onto Vector to be projected onto.
		 * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		 * @return Projected vector.
		 */
		template<typename S>
		Vector2D<T> reject(const Vector2D<S>& onto, bool ontoNormalized = false) const;


		static T dot(const Vector2D& vecA, const Vector2D& vecB);
		static T cross(const Vector2D& vecA, const Vector2D& vecB);

		// TODO: Refactor with enable_if_t for S

		/**
		 * Static wrapper for vector projection.
		 * @tparam S Type of the vector to be projected to.
		 * @param vector Vector to project.
		 * @param onto Vector to be projected onto.
		 * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		 * @return Projected vector.
		 */
		template<typename S>
		static Vector2D project(const Vector2D& vector, const Vector2D<S>& onto, bool ontoNormalized = false);

		/**
		 * Returns the perpendicular component for the current vector after projection to the `onto` vector.
		 * @tparam S Type of the vector to be vector projected onto.
		 * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
		 * @param onto Vector to be projected onto.
		 * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		 * @return Projected vector.
		 */
		template<typename S>
		static Vector2D reject(const Vector2D& vector, const Vector2D<S>& onto, bool ontoNormalized = false);
	};

	template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
	Vector2D<T> operator*(S scalar, const Vector2D<T>& vector);

	using vec2 = Vector2D<float>;
	using dvec2 = Vector2D<double>;
}

#include "Vector2D.tpp"