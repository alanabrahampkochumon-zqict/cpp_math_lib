#pragma once

#include <cstddef>

#include "../MathTraits.h"
#include "../vector/Vector4D.h"

namespace math
{
	template <Arithmetic T>
	struct alignas(16) Matrix4D
	{
		using value_type = T;

		static constexpr std::size_t columns = 4;
		static constexpr std::size_t rows = 4;

		union
		{
			//Vector4D<T> col_vectors[columns]; TODO: Add in after refactor vec4d to support type promotion
			T elements[columns][rows];
		};

		Matrix4D();
		Matrix4D(
			T v_0_0, T v_0_1, T v_0_2, T v_0_3,
			T v_1_0, T v_1_1, T v_1_2, T v_1_3,
			T v_2_0, T v_2_1, T v_2_2, T v_2_3,
			T v_3_0, T v_3_1, T v_3_2, T v_3_3
		);


		T& operator()(std::size_t row, std::size_t col);
		const T& operator()(std::size_t row, std::size_t col) const;
	};
	
}

#include "Matrix4D.tpp"