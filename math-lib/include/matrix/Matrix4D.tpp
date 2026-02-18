#pragma once

namespace math
{
	template <arithmetic T>
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
}
