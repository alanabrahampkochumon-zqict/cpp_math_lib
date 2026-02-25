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
	Vector4D<T>::Vector4D(T v1, T v2, T v3, T v4) : x(v1), y(v2), z(v3), w(v4) { }

	template <Arithmetic T>
	Vector4D<T>::Vector4D(Vector2D<T> vec1, Vector2D<T> vec2) : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) { }

	template <Arithmetic T>
	Vector4D<T>::Vector4D(Vector3D<T> vec, T v) : x(vec.x), y(vec.y), z(vec.z), w(v) { }

	template <Arithmetic T>
	template <Arithmetic U>
	Vector4D<T>::Vector4D(const Vector4D<U>& other) :
		x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w))
	{ }


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
	template <Arithmetic U>
	auto Vector4D<T>::operator+(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
	{
		using R = std::common_type_t<T, U>;
		return Vector4D<R>(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	template <Arithmetic T>
	template <Arithmetic U>
	Vector4D<T>& Vector4D<T>::operator+=(const Vector4D<U>& other)
	{
		x += static_cast<T>(other.x);
		y += static_cast<T>(other.y);
		z += static_cast<T>(other.z);
		w += static_cast<T>(other.w);
		return *this;
	}


	template <Arithmetic T>
	template <Arithmetic U>
	auto Vector4D<T>::operator-(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
	{
		using R = std::common_type_t<T, U>;
		return Vector4D<R>(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	template <Arithmetic T>
	template <Arithmetic U>
	Vector4D<T>& Vector4D<T>::operator-=(const Vector4D<U>& other)
	{
		x -= static_cast<T>(other.x);
		y -= static_cast<T>(other.y);
		z -= static_cast<T>(other.z);
		w -= static_cast<T>(other.w);
		return *this;
	}


	template <Arithmetic T>
	template <Arithmetic S>
	auto Vector4D<T>::operator*(const S& scalar) const -> Vector4D<std::common_type_t<T, S>>
	{

		using R = std::common_type_t<T, S>;
		return Vector4D<R>(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	template<Arithmetic T, Arithmetic S>
	auto operator*(S scalar, const Vector4D<T>& vector) -> Vector4D<std::common_type_t<T, S>>
	{
		return vector * scalar;
	}

	template <Arithmetic T>
	template <Arithmetic S>
	Vector4D<T>& Vector4D<T>::operator*=(const S& scalar)
	{

		x = static_cast<T>(scalar * x);
		y = static_cast<T>(scalar * y);
		z = static_cast<T>(scalar * z);
		w = static_cast<T>(scalar * w);
		return *this;
	}

	template <Arithmetic T>
	template <Arithmetic S>
	auto Vector4D<T>::operator/(const S& scalar) const -> Vector4D<std::common_type_t<T, S>>
	{
		using R = std::common_type_t<T, S>;
		if constexpr (std::is_floating_point_v<R>)
		{
			R factor = R(1) / static_cast<R>(scalar);
			return Vector4D<R>(x * factor, y * factor, z * factor, w * factor);

		}
		else
		{
			assert(scalar != 0 && "Integral division by zero");
			return Vector4D<R>(x / static_cast<T>(scalar), y / static_cast<T>(scalar), z / static_cast<T>(scalar), w / static_cast<T>(scalar));
		}
	}

	template <Arithmetic T>
	template <Arithmetic S>
	Vector4D<T>& Vector4D<T>::operator/=(const S& scalar)
	{
		using R = std::common_type_t<T, S>;
		if constexpr (std::is_floating_point_v<R>)
		{
			R factor = R(1) / static_cast<R>(scalar);

			x = static_cast<T>(factor * x);
			y = static_cast<T>(factor * y);
			z = static_cast<T>(factor * z);
			w = static_cast<T>(factor * w);
		}
		else
		{
			assert(scalar != 0 && "Integral division by zero");
			x /= static_cast<T>(scalar);
			y /= static_cast<T>(scalar);
			z /= static_cast<T>(scalar);
			w /= static_cast<T>(scalar);
		}

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
