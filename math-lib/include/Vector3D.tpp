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

	Vector3D math::Vector3D::operator-(const Vector3D& another) const
	{
		return Vector3D(x - another.x, y - another.y, z - another.z);
	}

	float math::Vector3D::mag() const
	{
		
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
}
