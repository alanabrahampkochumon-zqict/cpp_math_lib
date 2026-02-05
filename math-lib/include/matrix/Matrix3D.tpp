#pragma once

#include <type_traits>
#include "Matrix3D.h"

namespace math
{
	template<typename T>
	Matrix3D<T>::Matrix3D()
	{
		// Column Major
		// First Column
		elements[0][0] = T(1);
		elements[0][1] = T(0);
		elements[0][2] = T(0);

		// Second Column
		elements[1][0] = T(0);
		elements[1][1] = T(1);
		elements[1][2] = T(0);

		// Third Column
		elements[2][0] = T(0);
		elements[2][1] = T(0);
		elements[2][2] = T(1);
	}

	template <typename T>
	Matrix3D<T>::Matrix3D(
		T v_0_0, T v_0_1, T v_0_2,
		T v_1_0, T v_1_1, T v_1_2,
		T v_2_0, T v_2_1, T v_2_2
	)
	{
		// Column Major
		// First Column
		elements[0][0] = v_0_0;
		elements[0][1] = v_1_0;
		elements[0][2] = v_2_0;

		// Second Column
		elements[1][0] = v_0_1;
		elements[1][1] = v_1_1;
		elements[1][2] = v_2_1;

		// Third Column
		elements[2][0] = v_0_2;
		elements[2][1] = v_1_2;
		elements[2][2] = v_2_2;
	}

	template <typename T>
	Matrix3D<T>::Matrix3D(Vector3D<T> vec1, Vector3D<T> vec2, Vector3D<T> vec3)
	{
		columns[0] = vec1;
		columns[1] = vec2;
		columns[2] = vec3;
	}

	/**
	 * Stores a <Vector3D> instance to the specified column of the matrix.
	 * @param index column index of the matrix.
	 * @return alias to the layout of the memory that stores the vector.
	 */
	template <typename T>
	Vector3D<T>& Matrix3D<T>::operator[](size_t index)
	{
		return columns[index];
	}

	/**
	 * Retrieves <Vector3D> instance from a specific column of the matrix.
	 * @param index column index of the matrix.
	 * @return alias to the layout of the memory that stores the vector.
	 */
	template <typename T>
	const Vector3D<T>& Matrix3D<T>::operator[](size_t index) const
	{
		return columns[index];
	}

	template <typename T>
	T& Matrix3D<T>::operator()(size_t row, size_t col)
	{
		// We swap the rows and columns since internally we use column major order.
		return elements[col][row];
	}

	template <typename T>
	const T& Matrix3D<T>::operator()(size_t row, size_t col) const
	{
		// We swap the rows and columns since internally we use column major order.
		return elements[col][row];
	}

	/*************************************
	 *                                   *
	 *         MATH OPERATIONS           *
	 *                                   *
	 *************************************/

	template <typename T>
	Matrix3D<T> Matrix3D<T>::operator+(const Matrix3D& other) const
	{
		// Commented out for profiling
		//// Since `this` elements[0] is the first column, we need to take the rows first (this[c][r]) and add them to the r,c value of other
		//// to get the r,c value for the new matrix
		//return Matrix3D(
		//	// First Row
		//	elements[0][0] + other(0, 0), elements[1][0] + other(0, 1), elements[2][0] + other(0, 2),
		//	// Second Row
		//	elements[0][1] + other(1, 0), elements[1][1] + other(1, 1), elements[2][1] + other(1,2),
		//	// Third Row
		//	elements[0][2] + other(2, 0), elements[1][2] + other(2, 1), elements[2][2] + other(2,2)
		//);

		// Using Vector3D ops
		return Matrix3D(columns[0] + other[0], columns[1] + other[1], columns[2] + other[2]);
	}

	template <typename T>
	Matrix3D<T>& Matrix3D<T>::operator+=(const Matrix3D& other)
	{
		// NOTE: Commented out for profiling
		//// First Row
		//elements[0][0] += other(0, 0);
		//elements[1][0] += other(0, 1);
		//elements[2][0] += other(0, 2);
		//// Second Row
		//elements[0][1] += other(1, 0);
		//elements[1][1] += other(1, 1);
		//elements[2][1] += other(1, 2);
		//// Third Row
		//elements[0][2] += other(2, 0);
		//elements[1][2] += other(2, 1);
		//elements[2][2] += other(2, 2);

		columns[0] += other[0];
		columns[1] += other[1];
		columns[2] += other[2];

		return *this;
	}

	template <typename T>
	Matrix3D<T> Matrix3D<T>::operator-(const Matrix3D& other) const
	{
		// NOTE: Commented out for profiling
		//// Since `this` elements[0] is the first column, we need to take the rows first (this[c][r]) and add them to the r,c value of other
		//// to get the r,c value for the new matrix
		//return Matrix3D(
		//	// First Row
		//	elements[0][0] - other(0, 0), elements[1][0] - other(0, 1), elements[2][0] - other(0, 2),
		//	// Second Row
		//	elements[0][1] - other(1, 0), elements[1][1] - other(1, 1), elements[2][1] - other(1, 2),
		//	// Third Row
		//	elements[0][2] - other(2, 0), elements[1][2] - other(2, 1), elements[2][2] - other(2, 2)
		//);

		// Using Vector3D ops
		return Matrix3D(columns[0] - other[0], columns[1] - other[1], columns[2] - other[2]);
	}

	template <typename T>
	Matrix3D<T>& Matrix3D<T>::operator-=(const Matrix3D& other)
	{
		// NOTE: Commented out for profiling
		//// First Row
		//elements[0][0] -= other(0, 0);
		//elements[1][0] -= other(0, 1);
		//elements[2][0] -= other(0, 2);
		//// Second Row
		//elements[0][1] -= other(1, 0);
		//elements[1][1] -= other(1, 1);
		//elements[2][1] -= other(1, 2);
		//// Third Row
		//elements[0][2] -= other(2, 0);
		//elements[1][2] -= other(2, 1);
		//elements[2][2] -= other(2, 2);

		// Using Vector3D ops
		columns[0] -= other[0];
		columns[1] -= other[1];
		columns[2] -= other[2];

		return *this;
	}

	template<typename T>
	template <typename S, typename>
	Matrix3D<T> Matrix3D<T>::operator*(const S& scalar) const
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");

		return Matrix3D(columns[0] * scalar, columns[1] * scalar, columns[2] * scalar);
	}

	template<typename T>
	template <typename S, typename>
	Matrix3D<T>& Matrix3D<T>::operator*=(const S& scalar)
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");

		columns[0] *= scalar;
		columns[1] *= scalar;
		columns[2] *= scalar;
		return *this;
	}

	template<typename T>
	template <typename S, typename>
	Matrix3D<T> Matrix3D<T>::operator/(const S& scalar) const
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");


		T factor = T(1) / static_cast<T>(scalar);
		return Matrix3D(columns[0] * factor, columns[1] * factor, columns[2] * factor);

	}

	template<typename T>
	template <typename S, typename>
	Matrix3D<T>& Matrix3D<T>::operator/=(const S& scalar)
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");

		T factor = T(1) / static_cast<T>(scalar);
		columns[0] *= factor;
		columns[1] *= factor;
		columns[2] *= factor;

		return *this;
	}

	template <typename T>
	template <typename S, typename>
	Vector3D<T> Matrix3D<T>::operator*(const Vector3D<S>& vec) const
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
		return Vector3D(
			elements[0][0] * vec.x + elements[1][0] * vec.y + elements[2][0] * vec.z, // First Row * Vec
			elements[0][1] * vec.x + elements[1][1] * vec.y + elements[2][1] * vec.z, // Second Row * Vec
			elements[0][2] * vec.x + elements[1][2] * vec.y + elements[2][2] * vec.z  // Third Row * Vec
		);
	}

	template <typename T>
	template <typename S, typename>
	Matrix3D<T> Matrix3D<T>::operator*(const Matrix3D<S>& other) const
	{

		// TODO: Profiling
		//return Matrix3D(
		//	// First Row * Columns
		//	elements[0][0] * other(0, 0) + elements[1][0] * other(1, 0) + elements[2][0] * other(2, 0), elements[0][0] * other(0, 1) + elements[1][0] * other(1, 1) + elements[2][0] * other(2, 1), elements[0][0] * other(0, 2) + elements[1][0] * other(1, 2) + elements[2][0] * other(2, 2),
		//	// Second Row * Columns
		//	elements[0][1] * other(0, 0) + elements[1][1] * other(1, 0) + elements[2][1] * other(2, 0), elements[0][1] * other(0, 1) + elements[1][1] * other(1, 1) + elements[2][1] * other(2, 1), elements[0][1] * other(0, 2) + elements[1][1] * other(1, 2) + elements[2][1] * other(2, 2),
		//	// Third Row * Columns
		//	elements[0][2] * other(0, 0) + elements[1][2] * other(1, 0) + elements[2][2] * other(2, 0), elements[0][2] * other(0, 1) + elements[1][2] * other(1, 1) + elements[2][2] * other(2, 1), elements[0][2] * other(0, 2) + elements[1][2] * other(1, 2) + elements[2][2] * other(2, 2)
		//);

		return Matrix3D(
			// Matrix * First Column Vector
			(*this) * other[0],
			// Matrix * Second Column Vector
			(*this) * other[1],
			// Matrix * Third Column Vector
			(*this) * other[2]
		);
	}

	template <typename T>
	template <typename S, typename>
	Matrix3D<T>& Matrix3D<T>::operator*=(const Matrix3D<S>& other)
	{
		Matrix3D<T> result = (*this) * other;

		*this = result;

		return *this;
	}

	template <typename T>
	T Matrix3D<T>::determinant() const
	{
		// Evaluated along first column
		return elements[0][0] * (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1])
			- elements[0][1] * (elements[1][0] * elements[2][2] - elements[1][2] * elements[2][0])
			+ elements[0][2] * (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);
	}

	template <typename T>
	T Matrix3D<T>::determinant(const Matrix3D<T>& matrix)
	{
		return matrix.determinant();
	}

	template <typename T>
	Matrix3D<T> Matrix3D<T>::transpose() const
	{
		return *this;
	}

	template <typename T>
	Matrix3D<T> Matrix3D<T>::transpose(const Matrix3D<T>& matrix)
	{
		return Matrix3D();
	}


	template<typename T, typename S, typename>
	Matrix3D<T> operator*(const S& scalar, const Matrix3D<T>& matrix)
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
		return Matrix3D(matrix[0] * scalar, matrix[1] * scalar, matrix[2] * scalar);
	}

	template <typename T, typename S, typename>
	Vector3D<T> operator*(const Vector3D<S>& vec, const Matrix3D<T>& mat)
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
		return Vector3D(
			Vector3D<T>::dot(vec, mat[0]),
			Vector3D<T>::dot(vec, mat[1]),
			Vector3D<T>::dot(vec, mat[2])
		);
	}

	template <typename T, typename S, typename>
	Vector3D<T> operator*=(Vector3D<S>& vec, const Matrix3D<T>& mat)
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
		vec = Vector3D(
			Vector3D<T>::dot(vec, mat[0]),
			Vector3D<T>::dot(vec, mat[1]),
			Vector3D<T>::dot(vec, mat[2])
		);
		return vec;
	}
}
