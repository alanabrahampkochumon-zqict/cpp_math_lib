#pragma once
#include <cstddef>
#include <type_traits>

#include "vector/Vector3D.h"

namespace math
{
	template<typename T>
	struct Matrix3D
	{
		static_assert(std::is_floating_point_v<T>, "Matrix3D can only be instantiated with floats(float and double)");

	private:
		union
		{
			Vector3D<T> columns[3];
			T elements[3][3];
		};

	public:
		Matrix3D();
		Matrix3D(T v_0_0, T v_0_1, T v_0_2, T v_1_0, T v_1_1, T v_1_2, T v_2_0, T v_2_1, T v_2_2);
		Matrix3D(Vector3D<T> vec1, Vector3D<T> vec2, Vector3D<T> vec3);

		Vector3D<T>& operator[](size_t index);
		const Vector3D<T>& operator[](size_t index) const;

		T& operator()(size_t row, size_t col);
		const T& operator()(size_t row, size_t col) const;

		// Math Operators
		Matrix3D operator+(const Matrix3D& other) const;
		Matrix3D& operator+=(const Matrix3D& other);

		Matrix3D operator-(const Matrix3D& other) const;
		Matrix3D& operator-=(const Matrix3D& other);

		template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Matrix3D operator*(const S& scalar) const;
		template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Matrix3D& operator*=(const S& scalar);

		template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Matrix3D operator/(const S& scalar) const;
		template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Matrix3D& operator/=(const S& scalar);

		template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Vector3D<T> operator*(const Vector3D<S>& vec) const;

		template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Matrix3D<T> operator*(const Matrix3D<S>& other) const;

		/**
		 * Multiplies a matrix by a matrix with *= operator.
		 * NOTE: Not recommended for game engine, since it involves object copying.
		 * RECOMMENDED: Use Mat * Mat
		 * @tparam S Type of the other Matrix
		 * @param other The matrix to be multiplied with.
		 * @return Matrix on which *= is called, but with new values
		 */
		template<typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
		Matrix3D<T>& operator*=(const Matrix3D<S>& other);


	};

	template<typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
	Matrix3D<T> operator*(const S& scalar, const Matrix3D<T>& matrix);

	/**
	 * Multiplies a Vector3D by a Matrix3D.
	 * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
	 * @tparam T Type for matrix values
	 * @tparam S Type for vector values
	 * @param vec vector to be multiplied.
	 * @param mat matrix to be multiplied against.
	 * @return a new Vector3D transposed(row major form)
	 */
	template<typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
	Vector3D<T> operator*(const Vector3D<S>& vec, const Matrix3D<T>& mat);

	/**
	 * Multiplies a Vector3D by a Matrix3D.
	 * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
	 * NOTE: This operation returns a new vector so it is strictly for testing purposes and completeness and is not desirable to be used in game engine.
	 * @tparam T Type for matrix values
	 * @tparam S Type for vector values
	 * @param vec vector to be multiplied.
	 * @param mat matrix to be multiplied against.
	 * @return the passed in vector
	 */
	template<typename T, typename  S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
	Vector3D<T> operator*=(Vector3D<S>& vec, const Matrix3D<T>& mat);

}

#include "Matrix3D.tpp"