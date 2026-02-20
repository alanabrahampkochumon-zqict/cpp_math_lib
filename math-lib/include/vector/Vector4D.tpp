#pragma once

namespace math
{
	/*************************************
	 *                                   *
	 *            INITIALIZERS           *
	 *                                   *
	 *************************************/
	template <Arithmetic T>
	Vector4D<T>::Vector4D() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) { }

	template <Arithmetic T>
	Vector4D<T>::Vector4D(T v1, T v2, T v3, T v4): x(v1), y(v2), z(v3), w(v4) { }

	template <Arithmetic T>
	Vector4D<T>::Vector4D(Vector2D<T> vec1, Vector2D<T> vec2): x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) { }

	template <Arithmetic T>
	Vector4D<T>::Vector4D(Vector3D<T> vec, T v): x(vec.x), y(vec.y), z(vec.z), w(v)	{ }


	/*************************************
	 *                                   *
	 *            ACCESSORS              *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	T& Vector4D<T>::operator[](std::size_t i)
	{
		return (&x)[i];
	}

	template <Arithmetic T>
	const T& Vector4D<T>::operator[](std::size_t i) const
	{
		return (&x)[i];
	}


	/*************************************
	 *                                   *
	 *      ARITHMETIC OPERATORS         *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	Vector4D<T> Vector4D<T>::operator+(const Vector4D& other) const
	{
		return Vector4D(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	template <Arithmetic T>
	Vector4D<T>& Vector4D<T>::operator+=(const Vector4D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	template <Arithmetic T>
	Vector4D<T> Vector4D<T>::operator-(const Vector4D& other) const
	{
		return Vector4D(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	template <Arithmetic T>
	Vector4D<T>& Vector4D<T>::operator-=(const Vector4D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	template <Arithmetic T>
	template <Arithmetic S>
	Vector4D<T> Vector4D<T>::operator*(const S& scalar) const
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");

		return Vector4D(x * static_cast<T>(scalar), y * static_cast<T>(scalar), z * static_cast<T>(scalar), w * static_cast<T>(scalar));
	}

	template<Arithmetic T, Arithmetic S>
	Vector4D<T> operator*(S scalar, const Vector4D<T>& vector)
	{
		return vector * scalar;
	}

	template <Arithmetic T>
	template <Arithmetic S>
	Vector4D<T>& Vector4D<T>::operator*=(const S& scalar)
	{
		static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");

		x *= static_cast<T>(scalar);
		y *= static_cast<T>(scalar);
		z *= static_cast<T>(scalar);
		w *= static_cast<T>(scalar);
		return *this;
	}

	template <Arithmetic T>
	template <Arithmetic M>
	Vector4D<T> Vector4D<T>::operator/(const M& scalar) const
	{
		T factor = T(1) / static_cast<T>(scalar);
		return Vector4D(x * factor, y * factor, z * factor, w * factor);
	}

	template <Arithmetic T>
	template <Arithmetic M>
	Vector4D<T>& Vector4D<T>::operator/=(const M& scalar)
	{
		T factor = T(1) / static_cast<T>(scalar);

		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
		
		return *this;
	}


	/*************************************
	 *                                   *
	 *         VECTOR MAGNITUDE          *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	T Vector4D<T>::mag() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}


	/*************************************
	 *                                   *
	 *       VECTOR NORMALIZATION        *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	Vector4D<T> Vector4D<T>::normalize() const
	{
		return *this / mag();
	}


	/*************************************
	 *                                   *
	 *        VECTOR DOT PRODUCT         *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	T Vector4D<T>::dot(const Vector4D& other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	template <Arithmetic T>
	T Vector4D<T>::dot(const Vector4D& vecA, const Vector4D& vecB)
	{
		return vecA.dot(vecB);
	}


	/*************************************
	 *                                   *
	 *        VECTOR PROJECTION          *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	template <Arithmetic S>
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

	template <Arithmetic T>
	template <Arithmetic S>
	Vector4D<T> Vector4D<T>::project(const Vector4D& vector, const Vector4D<S>& onto, bool ontoNormalized)
	{
		return vector.project(onto, ontoNormalized);
	}


	/*************************************
	 *                                   *
	 *         VECTOR REJECTION          *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	template <Arithmetic S>
	Vector4D<T> Vector4D<T>::reject(const Vector4D<S>& onto, bool ontoNormalized) const
	{
		return *this - this->project(onto, ontoNormalized);
	}

	template <Arithmetic T>
	template <Arithmetic S>
	Vector4D<T> Vector4D<T>::reject(const Vector4D& vector, const Vector4D<S>& onto, bool ontoNormalized)
	{
		return vector.reject(onto, ontoNormalized);
	}

}
