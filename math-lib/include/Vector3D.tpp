#include "Vector3D.h"

namespace math {
	Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}

	Vector3D::Vector3D(float v1, float v2, float v3) : x(v1), y(v2), z(v3) { }

	float& Vector3D::operator[](int i) { return ((&x)[i]); }

	const float& Vector3D::operator[](int i) const { return ((&x)[i]); }

	Vector3D Vector3D::operator+(const Vector3D& another) const
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

	Vector3D Vector3D::operator-(const Vector3D& another) const
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
		Vector3D copy = *this;
		copy *= scalar;
		return copy;
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
		Vector3D copy = *this;
		copy /= scalar;
		return copy;
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
		Vector3D copy = vector;
		copy *= scalar;
		return copy;
	}

	float math::Vector3D::mag() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	Vector3D Vector3D::normalize() const
	{
		return (*this) / mag();
	}

}
