#pragma once

#include <type_traits>
#include <valarray>

namespace math
{
	template <typename T>
	Matrix2D<T>::Matrix2D()
	{
	}

	template <typename T>
	Matrix2D<T>::Matrix2D(T v_0_0, T v_0_1, T v_1_0, T v_1_1)
	{
	}

	template <typename T>
	Matrix2D<T>::Matrix2D(Vector2D<T> vec1, Vector2D<T> vec2)
	{
	}

	template <typename T>
	Vector2D<T>& Matrix2D<T>::operator[](size_t index)
	{
	}

	template <typename T>
	const Vector2D<T>& Matrix2D<T>::operator[](size_t index) const
	{
	}

	template <typename T>
	T& Matrix2D<T>::operator()(size_t row, size_t col)
	{
	}

	template <typename T>
	const T& Matrix2D<T>::operator()(size_t row, size_t col) const
	{
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::operator+(const Matrix2D& other) const
	{
	}

	template <typename T>
	Matrix2D<T>& Matrix2D<T>::operator+=(const Matrix2D& other)
	{
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::operator-(const Matrix2D& other) const
	{
	}

	template <typename T>
	Matrix2D<T>& Matrix2D<T>::operator-=(const Matrix2D& other)
	{
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T> Matrix2D<T>::operator*(const S& scalar) const
	{
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T>& Matrix2D<T>::operator*=(const S& scalar)
	{
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T> Matrix2D<T>::operator/(const S& scalar) const
	{
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T>& Matrix2D<T>::operator/=(const S& scalar)
	{
	}

	template <typename T>
	template <typename S, typename>
	Vector2D<T> Matrix2D<T>::operator*(const Vector2D<S>& vec) const
	{
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<S>& other) const
	{
	}

	template <typename T>
	template <typename S, typename>
	Matrix2D<T>& Matrix2D<T>::operator*=(const Matrix2D<S>& other)
	{
	}

	template <typename T>
	T Matrix2D<T>::determinant() const
	{
	}

	template <typename T>
	T Matrix2D<T>::determinant(const Matrix2D<T>& matrix)
	{
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::transpose() const
	{
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::transpose(const Matrix2D& matrix)
	{
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::inverse() const
	{
	}

	template <typename T>
	Matrix2D<T> Matrix2D<T>::inverse(const Matrix2D& matrix)
	{
	}

	template <typename T, typename S, typename>
	Matrix2D<T> operator*(const S& scalar, const Matrix2D<T>& matrix)
	{
	}

	template <typename T, typename S, typename>
	Vector2D<T> operator*(const Vector2D<S>& vec, const Matrix2D<T>& mat)
	{
	}

	template <typename T, typename S, typename>
	Vector2D<T> operator*=(Vector2D<S>& vec, const Matrix2D<T>& mat)
	{
	}
}
