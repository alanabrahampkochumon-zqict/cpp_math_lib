#pragma once

namespace math
{
	/*************************************
	*                                   *
	*            INITIALIZERS           *
	*                                   *
	*************************************/

	template <Arithmetic T>
	Matrix4D<T>::Matrix4D()
	{
		// First Column
		elements[0][0] = 1;
		elements[0][1] = 0;
		elements[0][2] = 0;
		elements[0][3] = 0;

		// Second Column
		elements[1][0] = 0;
		elements[1][1] = 1;
		elements[1][2] = 0;
		elements[1][3] = 0;

		// Third Column
		elements[2][0] = 0;
		elements[2][1] = 0;
		elements[2][2] = 1;
		elements[2][3] = 0;

		// Fourth Column
		elements[3][0] = 0;
		elements[3][1] = 0;
		elements[3][2] = 0;
		elements[3][3] = 1;
	}

	template <Arithmetic T>
	Matrix4D<T>::Matrix4D(
		T v_0_0, T v_0_1, T v_0_2, T v_0_3,
		T v_1_0, T v_1_1, T v_1_2, T v_1_3,
		T v_2_0, T v_2_1, T v_2_2, T v_2_3,
		T v_3_0, T v_3_1, T v_3_2, T v_3_3)
	{
		// First Column
		elements[0][0] = v_0_0;
		elements[0][1] = v_1_0;
		elements[0][2] = v_2_0;
		elements[0][3] = v_3_0;

		// Second Column
		elements[1][0] = v_0_1;
		elements[1][1] = v_1_1;
		elements[1][2] = v_2_1;
		elements[1][3] = v_3_1;

		// Third Column
		elements[2][0] = v_0_2;
		elements[2][1] = v_1_2;
		elements[2][2] = v_2_2;
		elements[2][3] = v_3_2;

		// Fourth Column
		elements[3][0] = v_0_3;
		elements[3][1] = v_1_3;
		elements[3][2] = v_2_3;
		elements[3][3] = v_3_3;
	}

	/*************************************
	 *                                   *
	 *            ACCESSORS              *
	 *                                   *
	 *************************************/

	template <Arithmetic T>
	T& Matrix4D<T>::operator()(std::size_t row, std::size_t col)
	{
		return elements[col][row];
	}

	template <Arithmetic T>
	const T& Matrix4D<T>::operator()(std::size_t row, std::size_t col) const
	{
		return elements[col][row];
	}
}
