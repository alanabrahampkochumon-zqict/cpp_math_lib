#pragma once
#include <cstddef>

#include "vector/Vector3D.h"

namespace math
{
	template<typename T>
	struct Matrix3D
	{
		static_assert(std::is_floating_point_v<T>, "Matrix3D can only be instantiated with floats(float and double)");

	private:
		union
		{
			T elements[3][3];
		};

	public:
		Matrix3D();
		Matrix3D(T v_0_0, T v_0_1, T v_0_2, T v_1_0, T v_1_1, T v_1_2, T v_2_0, T v_2_1, T v_2_2);
		Matrix3D(Vector3D<T> vec1, Vector3D<T> vec2, Vector3D<T> vec3);

		Vector3D<T>& operator[](size_t index);
		const Vector3D<T>& operator[](size_t index) const;

		T& operator()(size_t row, size_t col);
		const T& operator()(size_t row, size_t col) const;
	};

}

#include "Matrix3D.tpp"