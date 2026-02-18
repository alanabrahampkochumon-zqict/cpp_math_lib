#pragma once

#include <type_traits>
#include "../MathTraits.h"

namespace math
{
	template <arithmetic T>
	struct Vector2D
	{
		static_assert(std::is_arithmetic_v<T>, "Vector2D can only be instantiated with numbers like floats, integers, etc.");

		using value_type = T;

		static constexpr std::size_t dimension = 2;

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


		T& operator[](std::size_t i);
		const T& operator[](std::size_t i) const;

		template<arithmetic U>
		auto operator+(const Vector2D<U>& other) const
			->Vector2D<std::common_type_t<U, T>>;

		template<arithmetic U>
		Vector2D& operator+=(const Vector2D<U>& other);

		template<arithmetic U>
		auto operator-(const Vector2D<U>& other) const -> Vector2D<std::common_type_t<T,U>>;

		template<arithmetic U>
		Vector2D& operator-=(const Vector2D<U>& other);

		template <arithmetic S>
		auto operator*(S scalar) const -> Vector2D<std::common_type_t<T, S>>;

		template <arithmetic S>
		Vector2D& operator*=(S scalar);

		template <arithmetic S>
		auto operator/(S scalar) const -> Vector2D<std::common_type_t<T, S>>;

		template <arithmetic S>
		Vector2D& operator/=(S scalar);

		template <arithmetic U>
		auto dot(const Vector2D<U>& other) const -> std::common_type_t<T, U>;

		template<arithmetic U>
		static auto dot(const Vector2D& vectorA, const Vector2D<U>& vectorB) ->std::common_type_t<T, U>;

		template<arithmetic U>
		auto cross(const Vector2D<U>& other) const -> std::common_type_t<T, U>;
		template<arithmetic U>
		static auto cross(const Vector2D<T>& vectorA, const Vector2D<U>& vectorB) -> std::common_type_t<T, U>;

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

	template <arithmetic T, arithmetic S>
	auto operator*(S scalar, const Vector2D<T>& vector) -> Vector2D<std::common_type_t<S, T>>;

	using vec2 = Vector2D<float>;
	using dvec2 = Vector2D<double>;
}

#include "Vector2D.tpp"