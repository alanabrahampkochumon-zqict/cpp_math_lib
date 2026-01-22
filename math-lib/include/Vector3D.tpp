#pragma once
#include "Vector3D.h"

namespace math {

	template <typename T>
	Vector3D<T>::Vector3D() : x(T(0)), y(T(0)), z(T(0)) {}


	template <typename T>
	Vector3D<T>::Vector3D(T v1, T v2, T v3) : x(v1), y(v2), z(v3) { }


	template <typename T>
	T& Vector3D<T>::operator[](int i) { return ((&x)[i]); }


	template <typename T>
	const T& Vector3D<T>::operator[](int i) const { return ((&x)[i]); }


	template <typename T>
	Vector3D<T> Vector3D<T>::operator+(const Vector3D& another) const
	{
		return Vector3D<T>(x + another.x, y + another.y, z + another.z);
	}


	template <typename T>
	Vector3D<T>& Vector3D<T>::operator+=(const Vector3D& another)
	{
		x += another.x;
		y += another.y;
		z += another.z;
		return *this;
	}


	template <typename T>
	Vector3D<T> Vector3D<T>::operator-(const Vector3D& another) const
	{

		return Vector3D<T>(x - another.x, y - another.y, z - another.z);
	}


	template <typename T>
	Vector3D<T>& Vector3D<T>::operator-=(const Vector3D& another)
	{
		x -= another.x;
		y -= another.y;
		z -= another.z;
		return *this;
	}


	template <typename T>
	template <typename M>
	Vector3D<T> Vector3D<T>::operator*(const M& scalar) const
	{
		static_assert(std::is_arithmetic_v<M>, "You can only perform multiplication with a number");
		Vector3D<T> copy = *this;
		copy *= scalar;
		return copy;
	}


	template <typename T>
	template <typename M>
	Vector3D<T>& Vector3D<T>::operator*=(const M& scalar)
	{
		static_assert(std::is_arithmetic_v<M>, "You can only perform multiplication with a number");
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return (*this);
	}


	template <typename T>
	template <typename M>
	Vector3D<T> Vector3D<T>::operator/(const M& scalar) const
	{
		static_assert(std::is_arithmetic_v<M>, "You can only perform division with a number");
		Vector3D<T> copy = *this;
		copy /= scalar;
		return copy;
	}


	template <typename T>
	template <typename M>
	Vector3D<T>& Vector3D<T>::operator/=(const M& scalar)
	{
		static_assert(std::is_arithmetic_v<M>, "You can only perform division with a number");
		T mFactor = T(1) / scalar;
		x *= mFactor;
		y *= mFactor;
		z *= mFactor;
		return (*this);
	}


	template <typename T, typename M>
	Vector3D<T> operator*(M scalar, const Vector3D<T>& vector)
	{
		static_assert(std::is_arithmetic_v<M>, "You can only perform division with a number");
		Vector3D<T> copy = vector;
		copy *= scalar;
		return copy;
	}


	template <typename T>
	T math::Vector3D<T>::mag() const
	{
		return sqrt(x*x + y*y + z*z);
	}


	template <typename T>
	Vector3D<T> Vector3D<T>::normalize() const
	{
		return (*this) / mag();
	}

}
