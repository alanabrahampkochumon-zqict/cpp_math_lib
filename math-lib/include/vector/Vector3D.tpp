#pragma once

// TODO: Enable strict types using `using R = std::common_type_t<T, S>`

namespace math {

	template <typename T>
	Vector3D<T>::Vector3D() : x(T(0)), y(T(0)), z(T(0)) {}


	template <typename T>
	Vector3D<T>::Vector3D(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

	template <typename T>
	Vector3D<T>::Vector3D(Vector2D<T> vec, T v) : x(vec.x), y(vec.y), z(v) {}

	template <typename T>
	template <typename S, typename>
	Vector3D<T>::Vector3D(const Vector3D<S>& other) :
		x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z))
	{ }

	template <typename T>
	T& Vector3D<T>::operator[](int i) { return ((&x)[i]); }


	template <typename T>
	const T& Vector3D<T>::operator[](int i) const { return ((&x)[i]); }

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::operator+(const Vector3D<S>& other) const -> Vector3D<std::common_type_t<T, S>>
	{
		using R = std::common_type_t<T, S>;
		return Vector3D<R>(x + other.x, y + other.y, z + other.z);
	}

	template <typename T>
	template <typename S, typename>
	Vector3D<T>& Vector3D<T>::operator+=(const Vector3D<S>& other)
	{
		x += static_cast<T>(other.x);
		y += static_cast<T>(other.y);
		z += static_cast<T>(other.z);
		return *this;
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::operator-(const Vector3D<S>& other) const -> Vector3D<std::common_type_t<T, S>>
	{
		return Vector3D(x - other.x, y - other.y, z - other.z);
	}

	template <typename T>
	template <typename S, typename>
	Vector3D<T>& Vector3D<T>::operator-=(const Vector3D<S>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::operator*(const S& scalar) const -> Vector3D<std::common_type_t<T, S>>
	{
		// TODO: Experiment with rvalue
		Vector3D copy = (*this);
		copy *= scalar;
		return copy;
	}


	template <typename T, typename S, typename, typename>
	auto operator*(S scalar, const Vector3D<T>& vector) -> Vector3D<std::common_type_t<T, S>>
	{
		return vector * scalar;
	}

	template <typename T>
	template <typename S, typename>
	Vector3D<T>& Vector3D<T>::operator*=(const S& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return (*this);
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::operator/(const S& scalar) const -> Vector3D<std::common_type_t<T, S>>
	{
		// TODO: Experiment with rvalue
		using R = std::common_type_t<T, S>;
		R factor = R(1) / scalar;
		return Vector3D(factor * x, factor * y, factor * z) ;
	}

	template <typename T>
	template <typename S, typename>
	Vector3D<T>& Vector3D<T>::operator/=(const S& scalar)
	{
		// TODO: Experiment with rvalue
		using R = std::common_type_t<T, S>;
		R mFactor = R(1) / scalar;
		x *= mFactor;
		y *= mFactor;
		z *= mFactor;
		return (*this);
	}

	template <typename T>
	T Vector3D<T>::mag() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	template <typename T>
	Vector3D<T> Vector3D<T>::normalize() const
	{
		return (*this) / mag();
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::dot(const Vector3D<S>& other) const -> std::common_type_t<T, S>
	{
		return x * other.x + y * other.y + z * other.z;
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::dot(const Vector3D& vecA, const Vector3D<S>& vecB) -> std::common_type_t<T, S>
	{
		return vecA.dot(vecB);
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::cross(const Vector3D<S>& other) const -> Vector3D<std::common_type_t<T, S>>
	{
		return Vector3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::cross(const Vector3D& vecA, const Vector3D<S>& vecB) -> Vector3D<std::common_type_t<T, S>>
	{
		return vecA.cross(vecB);
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::project(const Vector3D<S>& onto, bool ontoNormalized) const -> Vector3D<std::common_type_t<T, S>>
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

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::project(const Vector3D& vector, const Vector3D<S>& onto,
		bool ontoNormalized) -> Vector3D<std::common_type_t<T, S>>
	{
		return vector.project(onto, ontoNormalized);
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::reject(const Vector3D<S>& onto, bool ontoNormalized) const -> Vector3D<std::common_type_t<T, S>>
	{
		return *this - this->project(onto, ontoNormalized);
	}

	template <typename T>
	template <typename S, typename>
	auto Vector3D<T>::reject(const Vector3D& vector, const Vector3D<S>& onto,
		bool ontoNormalized) -> Vector3D<std::common_type_t<T, S>>
	{
		return vector.reject(onto, ontoNormalized);
	}

}


