#pragma once

namespace math
{
	template<typename T>
	Matrix3D<T>::Matrix3D()
	{
		// Column Major
		elements[0] = T(1);
		elements[3] = T(0);
		elements[6] = T(0);

		elements[1] = T(0);
		elements[4] = T(1);
		elements[7] = T(0);

		elements[2] = T(0);
		elements[5] = T(0);
		elements[8] = T(1);
	}

	template <typename T>
	Matrix3D<T>::Matrix3D(T v_0_0, T v_0_1, T v_0_2, T v_1_0, T v_1_1, T v_1_2, T v_2_0, T v_2_1, T v_2_2)
	{
		// Column Major
		elements[0] = v_0_0;
		elements[3] = v_0_1;
		elements[6] = v_0_2;

		elements[1] = v_1_0;
		elements[4] = v_1_1;
		elements[7] = v_1_2;

		elements[2] = v_2_0;
		elements[5] = v_2_1;
		elements[8] = v_2_2;
	}

	template <typename T>
	Matrix3D<T>::Matrix3D(Vector3D<T> vec1, Vector3D<T> vec2, Vector3D<T> vec3)
	{
		columns[0] = vec1;
		columns[1] = vec2;
		columns[2] = vec3;
	}

	template <typename T>
	Vector3D<T>& Matrix3D<T>::operator[](size_t index)
	{
		return columns[index];
	}

	template <typename T>
	const Vector3D<T>& Matrix3D<T>::operator[](size_t index) const
	{
		return columns[index];
	}

	template <typename T>
	T& Matrix3D<T>::operator()(size_t row, size_t col)
	{
		return columns[col][row];
	}

	template <typename T>
	const T& Matrix3D<T>::operator()(size_t row, size_t col) const
	{
		return columns[col][row];
	}
}
