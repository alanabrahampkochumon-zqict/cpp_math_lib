#pragma once

namespace math {

	template <typename T>
	Vector3D<T>::Vector3D() : x(T(0)), y(T(0)), z(T(0)) {}


	template <typename T>
	Vector3D<T>::Vector3D(T v1, T v2, T v3) : x(v1), y(v2), z(v3) { }

	template <typename T>
	Vector3D<T>::Vector3D(Vector2D<T> vec, T v): x(vec.x), y(vec.y), z(v) { }


	template <typename T>
	T& Vector3D<T>::operator[](int i) { return ((&x)[i]); }


	template <typename T>
	const T& Vector3D<T>::operator[](int i) const { return ((&x)[i]); }


	template <typename T>
	Vector3D<T> Vector3D<T>::operator+(const Vector3D& other) const
	{
		return Vector3D<T>(x + other.x, y + other.y, z + other.z);
	}


	template <typename T>
	Vector3D<T>& Vector3D<T>::operator+=(const Vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}


	template <typename T>
	Vector3D<T> Vector3D<T>::operator-(const Vector3D& other) const
	{

		return Vector3D<T>(x - other.x, y - other.y, z - other.z);
	}


	template <typename T>
	Vector3D<T>& Vector3D<T>::operator-=(const Vector3D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}


	template <typename T>
	template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
	Vector3D<T> Vector3D<T>::operator*(const S& scalar) const
	{
		static_assert(std::is_arithmetic_v<S>, "You can only perform multiplication with a number");
		Vector3D copy = *this;
		copy *= scalar;
		return copy;
	}

	template <typename T>
	template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
	Vector3D<T>& Vector3D<T>::operator*=(const S& scalar)
	{
		static_assert(std::is_arithmetic_v<S>, "You can only perform multiplication with a number");
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return (*this);
	}


	template <typename T>
	template <typename M>
	Vector3D<T> Vector3D<T>::operator/(const M& scalar) const
	{
		static_assert(std::is_arithmetic_v<M>, "scalar must be an integral or float(int, float, double, etc.)");
		Vector3D copy = *this;
		copy /= scalar;
		return copy;
	}


	template <typename T>
	template <typename M>
	Vector3D<T>& Vector3D<T>::operator/=(const M& scalar)
	{
		static_assert(std::is_arithmetic_v<M>, "scalar must be an integral or float(int, float, double, etc.)");
		T mFactor = T(1) / scalar;
		x *= mFactor;
		y *= mFactor;
		z *= mFactor;
		return (*this);
	}

	template <typename T>
	T Vector3D<T>::dot(const Vector3D& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	template <typename T>
	Vector3D<T> Vector3D<T>::cross(const Vector3D& other) const
	{
		return Vector3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}


	template <typename T, typename M>
	Vector3D<T> operator*(M scalar, const Vector3D<T>& vector)
	{
		static_assert(std::is_arithmetic_v<M>, "scalar must be an integral or float(int, float, double, etc.)");
		Vector3D<T> copy = vector;
		copy *= scalar;
		return copy;
	}


	template <typename T>
	T Vector3D<T>::mag() const
	{
		return sqrt(x*x + y*y + z*z);
	}


	template <typename T>
	Vector3D<T> Vector3D<T>::normalize() const
	{
		return (*this) / mag();
	}

	template <typename T>
	T Vector3D<T>::dot(const Vector3D& vecA, const Vector3D& vecB)
	{
		return vecA.dot(vecB);
	}

	template <typename T>
	Vector3D<T> Vector3D<T>::cross(const Vector3D& vecA, const Vector3D& vecB)
	{
		return vecA.cross(vecB);
	}
}


