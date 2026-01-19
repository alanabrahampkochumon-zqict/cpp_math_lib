#include "Vector3D.h"
using namespace math;

Vector3D::Vector3D() : x(1.0f), y(1.0f), z(1.0f) {}

Vector3D::Vector3D(float v1, float v2, float v3) : x(v1), y(v2), z(v3) { }

const Vector3D& math::Vector3D::operator+(const Vector3D& another)
{
	Vector3D res;

	res.x = this->x + another.x;
	res.y = this->y + another.y;
	res.z = this->z + another.z;

	return res;
}
