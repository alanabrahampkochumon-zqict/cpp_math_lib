#include "Vector3D.h"

namespace math {
	Vector3D::Vector3D() : x(1.0f), y(1.0f), z(1.0f) {}

	Vector3D::Vector3D(float v1, float v2, float v3) : x(v1), y(v2), z(v3) { }

	float& math::Vector3D::operator[](int i) { return ((&x)[i]); }

	const float& math::Vector3D::operator[](int i) const { return ((&x)[i]); }

	Vector3D math::Vector3D::operator+(const Vector3D& another) const
	{
		return Vector3D(x + another.x, y + another.y, z + another.z);
	}

	Vector3D& Vector3D::operator+=(const Vector3D& another)
	{
		x += another.x;
		y += another.y;
		z += another.z;
		return *this;
	}

	Vector3D math::Vector3D::operator-(const Vector3D& another) const
	{

		return Vector3D(x - another.x, y - another.y, z - another.z);
	}

	Vector3D& Vector3D::operator-=(const Vector3D& another)
	{
		x -= another.x;
		y -= another.y;
		z -= another.z;
		return *this;
	}

	Vector3D Vector3D::operator*(const float& scalar) const
	{
		return _times(*this, scalar);
	}

	Vector3D& Vector3D::operator*=(const float& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return (*this);
	}

	Vector3D Vector3D::operator/(const float& scalar) const
	{
		float factor = 1.0f / scalar;
		return _times(*this, factor);
	}

	Vector3D& Vector3D::operator/=(const float& scalar)
	{
		float mFactor = 1.0f / scalar;
		x *= mFactor;
		y *= mFactor;
		z *= mFactor;
		return (*this);
	}

	inline Vector3D operator*(float scalar, const Vector3D& vector)
	{
		return _times(vector, scalar);
	}

	float math::Vector3D::mag() const
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}


	/*
		PRIVATE FUNCTIONS/HELPERS
	*/
	inline Vector3D _times(const Vector3D& vec, const float scalar)
	{
		return Vector3D(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}
}
