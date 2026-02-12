#pragma once

namespace math
{
	template <typename T>
	Vector4D<T>::Vector4D() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) { }

	template <typename T>
	Vector4D<T>::Vector4D(T v1, T v2, T v3, T v4): x(v1), y(v2), z(v3), w(v4) { }

	template <typename T>
	Vector4D<T>::Vector4D(Vector2D<T> vec1, Vector2D<T> vec2): x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) { }

	template <typename T>
	Vector4D<T>::Vector4D(Vector3D<T> vec, T v): x(vec.x), y(vec.y), z(vec.z), w(v)	{ }

	template <typename T>
	T& Vector4D<T>::operator[](int i)
	{
		return (&x)[i];
	}

	template <typename T>
	const T& Vector4D<T>::operator[](int i) const
	{
		return (&x)[i];
	}

	template <typename T>
	Vector4D<T> Vector4D<T>::operator+(const Vector4D& other) const
	{
		return Vector4D(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	template <typename T>
	Vector4D<T>& Vector4D<T>::operator+=(const Vector4D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	template <typename T>
	Vector4D<T> Vector4D<T>::operator-(const Vector4D& other) const
	{
		return Vector4D(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	template <typename T>
	Vector4D<T>& Vector4D<T>::operator-=(const Vector4D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	template <typename T>
	template <typename S, typename>
	Vector4D<T> Vector4D<T>::operator*(const S& scalar) const
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");

		return Vector4D(x * static_cast<T>(scalar), y * static_cast<T>(scalar), z * static_cast<T>(scalar), w * static_cast<T>(scalar));
	}

	template <typename T>
	template <typename S, typename>
	Vector4D<T>& Vector4D<T>::operator*=(const S& scalar)
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");

		x *= static_cast<T>(scalar);
		y *= static_cast<T>(scalar);
		z *= static_cast<T>(scalar);
		w *= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename M>
	Vector4D<T> Vector4D<T>::operator/(const M& scalar) const
	{
		static_assert(std::is_arithmetic_v<M>, "scalar must be an integral or float(int, float, double, etc.)");
		T factor = T(1) / static_cast<T>(scalar);
		return Vector4D(x * factor, y * factor, z * factor, w * factor);
	}

	template <typename T>
	template <typename M>
	Vector4D<T>& Vector4D<T>::operator/=(const M& scalar)
	{
		static_assert(std::is_arithmetic_v<M>, "scalar must be an integral or float(int, float, double, etc.)");
		T factor = T(1) / static_cast<T>(scalar);

		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
		
		return *this;
	}

	template <typename T>
	T Vector4D<T>::dot(const Vector4D& other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	template <typename T>
	T Vector4D<T>::mag() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	template <typename T>
	Vector4D<T> Vector4D<T>::normalize() const
	{
		return *this / mag();
	}

	template <typename T>
	T Vector4D<T>::dot(const Vector4D& vecA, const Vector4D& vecB)
	{
		return vecA.dot(vecB);
	}

	template <typename T>
	template <typename S>
	Vector4D<T> Vector4D<T>::project(const Vector4D<S>& onto, bool ontoNormalized) const
	{
		if (ontoNormalized)
		{
			// a.dot(b) * b
			return this->dot(onto) * onto;
		}
		else
		{
			// a.dot(b) / b.dot(b) * b
			return this->dot(onto) / onto.dot(onto) * onto;
		}
	}

	template <typename T>
	template <typename S>
	Vector4D<T> Vector4D<T>::reject(const Vector4D<S>& onto, bool ontoNormalized) const
	{
		return *this - this->project(onto, ontoNormalized);
	}

	template <typename T>
	template <typename S>
	Vector4D<T> Vector4D<T>::project(const Vector4D& vector, const Vector4D<S>& onto, bool ontoNormalized)
	{
		return vector.project(onto, ontoNormalized);
	}

	template <typename T>
	template <typename S>
	Vector4D<T> Vector4D<T>::reject(const Vector4D& vector, const Vector4D<S>& onto, bool ontoNormalized)
	{
		return vector.reject(onto, ontoNormalized);
	}

	template <typename T, typename M>
	Vector4D<T> operator*(M scalar, const Vector4D<T>& vector)
	{
		static_assert(std::is_arithmetic_v<M>, "scalar must be an integral or float(int, float, double, etc.)");
		return vector * scalar;
	}
}
