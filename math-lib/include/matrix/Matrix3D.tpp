#pragma once

namespace math
{
	template<typename T>
	Matrix3D<T>::Matrix3D()
	{
		// Column Major
		elements[0][0] = T(1);
		elements[0][1] = T(0);
		elements[0][2] = T(0);

		elements[1][0] = T(0);
		elements[1][1] = T(1);
		elements[1][2] = T(0);

		elements[2][0] = T(0);
		elements[2][1] = T(0);
		elements[2][2] = T(1);
	}

	template <typename T>
	Matrix3D<T>::Matrix3D(T v_0_0, T v_0_1, T v_0_2, T v_1_0, T v_1_1, T v_1_2, T v_2_0, T v_2_1, T v_2_2)
	{
		// Column Major
		elements[0][0] = v_0_0;
		elements[0][1] = v_1_0;
		elements[0][2] = v_2_0;

		elements[1][0] = v_0_1;
		elements[1][1] = v_1_1;
		elements[1][2] = v_2_1;

		elements[2][0] = v_0_2;
		elements[2][1] = v_1_2;
		elements[2][2] = v_2_2;
	}

	template <typename T>
	Matrix3D<T>::Matrix3D(Vector3D<T> vec1, Vector3D<T> vec2, Vector3D<T> vec3)
	{

		elements[0][0] = vec1.x;
		elements[0][1] = vec1.y;
		elements[0][2] = vec1.z;

		elements[1][0] = vec2.x;
		elements[1][1] = vec2.y;
		elements[1][2] = vec2.z;

		elements[2][0] = vec3.x;
		elements[2][1] = vec3.y;
		elements[2][2] = vec3.z;
	}

	template <typename T>
	Vector3D<T>& Matrix3D<T>::operator[](size_t index)
	{
		return (*reinterpret_cast<Vector3D<T>*>(elements[index]));
	}

	template <typename T>
	const Vector3D<T>& Matrix3D<T>::operator[](size_t index) const
	{
		return (*reinterpret_cast<Vector3D<T>*>(elements[index]));
	}

	template <typename T>
	T& Matrix3D<T>::operator()(size_t row, size_t col)
	{
		return elements[col][row];
	}

	template <typename T>
	const T& Matrix3D<T>::operator()(size_t row, size_t col) const
	{
		return elements[col][row];
	}
}
