#pragma once

// TODO: Enable strict types using `using R = std::common_type_t<T, U>`

namespace math {

	template <arithmetic T>
	Vector3D<T>::Vector3D() : x(T(0)), y(T(0)), z(T(0)) {}

	template <arithmetic T>
	Vector3D<T>::Vector3D(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

	template <arithmetic T>
	Vector3D<T>::Vector3D(Vector2D<T> vec, T v) : x(vec.x), y(vec.y), z(v) {}

	template <arithmetic T>
	template <arithmetic U>
	Vector3D<T>::Vector3D(const Vector3D<U>& other) :
		x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z))
	{ }


	template <arithmetic T>
	T& Vector3D<T>::operator[](std::size_t i) { return ((&x)[i]); }

	template <arithmetic T>
	const T& Vector3D<T>::operator[](std::size_t i) const { return ((&x)[i]); }


	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::operator+(const Vector3D<U>& other) const -> Vector3D<std::common_type_t<T, U>>
	{
		using R = std::common_type_t<T, U>;
		return Vector3D<R>(x + other.x, y + other.y, z + other.z);
	}

	template <arithmetic T>
	template <arithmetic U>
	Vector3D<T>& Vector3D<T>::operator+=(const Vector3D<U>& other)
	{
		x += static_cast<T>(other.x);
		y += static_cast<T>(other.y);
		z += static_cast<T>(other.z);
		return *this;
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::operator-(const Vector3D<U>& other) const -> Vector3D<std::common_type_t<T, U>>
	{
		using R = std::common_type_t<T, U>;
		return Vector3D<R>(x - other.x, y - other.y, z - other.z);
	}

	template <arithmetic T>
	template <arithmetic U>
	Vector3D<T>& Vector3D<T>::operator-=(const Vector3D<U>& other)
	{
		x -= static_cast<T>(other.x);
		y -= static_cast<T>(other.y);
		z -= static_cast<T>(other.z);
		return *this;
	}

	template <arithmetic T>
	template <arithmetic S>
	auto Vector3D<T>::operator*(S scalar) const -> Vector3D<std::common_type_t<T, S>>
	{
		// TODO: Experiment with rvalue
		Vector3D copy = (*this);
		copy *= scalar;
		return copy;
	}


	template <arithmetic T, arithmetic S>
	auto operator*(S scalar, const Vector3D<T>& vector) -> Vector3D<std::common_type_t<T, S>>
	{
		return vector * scalar;
	}

	template <arithmetic T>
	template <arithmetic S>
	Vector3D<T>& Vector3D<T>::operator*=(S scalar)
	{
		x = static_cast<T>(scalar * x);
		y = static_cast<T>(scalar * y);
		z = static_cast<T>(scalar * z);
		return (*this);
	}

	template <arithmetic T>
	template <arithmetic S>
	auto Vector3D<T>::operator/(S scalar) const -> Vector3D<std::common_type_t<T, S>>
	{
		// TODO: Experiment with rvalue
		using R = std::common_type_t<T, S>;
		R factor = R(1) / scalar;
		return Vector3D<R>(factor * x, factor * y, factor * z) ;
	}

	template <arithmetic T>
	template <arithmetic S>
	Vector3D<T>& Vector3D<T>::operator/=(S scalar)
	{
		using R = std::common_type_t<T, S>;
		R factor = R(1) / scalar;
		x = static_cast<T>(x * factor);
		y = static_cast<T>(y * factor);
		z = static_cast<T>(z * factor);
		return (*this);
	}

	template <arithmetic T>
	T Vector3D<T>::mag() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	template <arithmetic T>
	Vector3D<T> Vector3D<T>::normalize() const
	{
		return (*this) / mag();
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::dot(const Vector3D<U>& other) const -> std::common_type_t<T, U>
	{
		return x * other.x + y * other.y + z * other.z;
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::dot(const Vector3D& vecA, const Vector3D<U>& vecB) -> std::common_type_t<T, U>
	{
		return vecA.dot(vecB);
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::cross(const Vector3D<U>& other) const -> Vector3D<std::common_type_t<T, U>>
	{
		using R = std::common_type_t<T, U>;
		return Vector3D<R>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::cross(const Vector3D& vecA, const Vector3D<U>& vecB) -> Vector3D<std::common_type_t<T, U>>
	{
		return vecA.cross(vecB);
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::project(const Vector3D<U>& onto, bool ontoNormalized) const -> Vector3D<std::common_type_t<T, U>>
	{
		if (ontoNormalized)
		{
			// Pb||a^ = a.dot(b) * b
			return this->dot(onto) * onto;
		}
		else
		{
			// Pb||a^ = a.dot(b) / b.dot(b) * b
			return this->dot(onto) / onto.dot(onto) * onto;
		}
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::project(const Vector3D& vector, const Vector3D<U>& onto,
		bool ontoNormalized) -> Vector3D<std::common_type_t<T, U>>
	{
		return vector.project(onto, ontoNormalized);
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::reject(const Vector3D<U>& onto, bool ontoNormalized) const -> Vector3D<std::common_type_t<T, U>>
	{
		return *this - this->project(onto, ontoNormalized);
	}

	template <arithmetic T>
	template <arithmetic U>
	auto Vector3D<T>::reject(const Vector3D& vector, const Vector3D<U>& onto,
		bool ontoNormalized) -> Vector3D<std::common_type_t<T, U>>
	{
		return vector.reject(onto, ontoNormalized);
	}

}


