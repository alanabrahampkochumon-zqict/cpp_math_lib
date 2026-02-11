#pragma once

#include <type_traits>
#include <valarray>

namespace math
{
	template <typename T>
	Matrix2D<T>::Matrix2D()
	{
		// First Column
		elements[0][0] = 1;
		elements[0][1] = 0;

		// Second Column
		elements[1][0] = 0;
		elements[1][1] = 1;
	}

	template <typename T>
	Matrix2D<T>::Matrix2D(T v_0_0, T v_0_1, T v_1_0, T v_1_1)
	{
		// First Column
		elements[0][0] = v_0_0;
		elements[0][1] = v_1_0;

		// Second Column
		elements[1][0] = v_0_1;
		elements[1][1] = v_1_1;
	}

	template <typename T>
	Matrix2D<T>::Matrix2D(Vector2D<T> vec1, Vector2D<T> vec2)
	{
		columns[0] = vec1;
		columns[1] = vec2;
	}

	template <typename T>
	Vector2D<T>& Matrix2D<T>::operator[](size_t index)
	{
		return columns[index];
	}

	template <typename T>
	const Vector2D<T>& Matrix2D<T>::operator[](size_t index) const
	{
		return columns[index];
	}

	template <typename T>
	T& Matrix2D<T>::operator()(size_t row, size_t col)
	{
		return elements[col][row];
	}

	template <typename T>
	const T& Matrix2D<T>::operator()(size_t row, size_t col) const
	{
		return elements[col][row];
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::operator+(const Matrix2D& other) const
	{
		return Matrix2D(
			elements[0][0] + other(0, 0), elements[1][0] + other(0, 1),
			elements[0][1] + other(1, 0), elements[1][1] + other(1, 1)
		);
	}

	template <typename T>
	Matrix2D<T>& Matrix2D<T>::operator+=(const Matrix2D& other)
	{
		elements[0][0] += other(0, 0);
		elements[1][0] += other(0, 1);
		elements[0][1] += other(1, 0);
		elements[1][1] += other(1, 1);

		return *this;
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::operator-(const Matrix2D& other) const
	{
		return Matrix2D(
			elements[0][0] - other(0, 0), elements[1][0] - other(0, 1),
			elements[0][1] - other(1, 0), elements[1][1] - other(1, 1)
		);
	}

	template <typename T>
	Matrix2D<T>& Matrix2D<T>::operator-=(const Matrix2D& other)
	{
		elements[0][0] -= other(0, 0);
		elements[1][0] -= other(0, 1);
		elements[0][1] -= other(1, 0);
		elements[1][1] -= other(1, 1);

		return *this;
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T> Matrix2D<T>::operator*(const S& scalar) const
	{
		return Matrix2D(
			elements[0][0] * scalar, elements[1][0] * scalar,
			elements[0][1] * scalar, elements[1][1] * scalar
		);
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T>& Matrix2D<T>::operator*=(const S& scalar)
	{	
		elements[0][0] *= scalar;
		elements[0][1] *= scalar;
		elements[1][0] *= scalar;
		elements[1][1] *= scalar;
		return *this;
	}

	template <typename T>
	template <typename S, typename>
	Vector2D<T> Matrix2D<T>::operator*(const Vector2D<S>& vec) const
	{
		// 0_0 1_0     x
		//           *
		// 0_1 1_1     y

		return Vector2D<T>(
			elements[0][0] * vec.x + elements[1][0] * vec.y,
			elements[0][1] * vec.x + elements[1][1] * vec.y
		);
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<S>& other) const
	{
		return Matrix2D<T>(
			elements[0][0] * other(0, 0) + elements[1][0] * other(1, 0), elements[0][0] * other(0, 1) + elements[1][0] * other(1, 1), 
			elements[0][1] * other(0, 0) + elements[1][1] * other(1, 0), elements[0][1] * other(0, 1) + elements[1][1] * other(1, 1) 
		);
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T>& Matrix2D<T>::operator*=(const Matrix2D<S>& other)
	{	
		Matrix2D&& temp = Matrix2D<T>(
			elements[0][0] * other(0, 0) + elements[1][0] * other(1, 0), elements[0][0] * other(0, 1) + elements[1][0] * other(1, 1),
			elements[0][1] * other(0, 0) + elements[1][1] * other(1, 0), elements[0][1] * other(0, 1) + elements[1][1] * other(1, 1)
		);
		(*this) = temp;

		return temp;
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T> Matrix2D<T>::operator/(const S& scalar) const
	{
		return Matrix2D<T>();
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T>& Matrix2D<T>::operator/=(const S& scalar)
	{
		return Matrix2D<T>();
	}

	template <typename T>
	T Matrix2D<T>::determinant() const
	{
		return T(0);
	}

	template <typename T>
	T Matrix2D<T>::determinant(const Matrix2D<T>& matrix)
	{
		return T(0);
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::transpose() const
	{
		return Matrix2D<T>();
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::transpose(const Matrix2D& matrix)
	{
		return Matrix2D<T>();
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::inverse() const
	{
		return Matrix2D<T>();
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::inverse(const Matrix2D& matrix)
	{
		return Matrix2D<T>();
	}

	template <typename T, typename S, typename>
	Matrix2D<T> operator*(const S& scalar, const Matrix2D<T>& matrix)
	{
		return matrix * scalar;
	}

	template <typename T, typename S, typename>
	Vector2D<T> operator*(const Vector2D<S>& vec, const Matrix2D<T>& mat)
	{
		return Vector2D(
			vec.x * mat(0, 0) + vec.y * mat(1, 0),
			vec.x * mat(0, 1) + vec.y * mat(1, 1)
		);
	}

	template <typename T, typename S, typename>
	Vector2D<T> operator*=(Vector2D<S>& vec, const Matrix2D<T>& mat)
	{
		vec = Vector2D(
			vec.x * mat(0, 0) + vec.y * mat(1, 0),
			vec.x * mat(0, 1) + vec.y * mat(1, 1)
		);
		return vec;
	}
}
