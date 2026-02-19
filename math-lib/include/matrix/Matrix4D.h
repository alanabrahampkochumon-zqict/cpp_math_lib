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
			Vector4D<T> col_vectors[columns];
			T elements[columns][rows];
		};

		Matrix4D();


		T& operator()(std::size_t row, std::size_t col);
		const T& operator()(std::size_t row, std::size_t col) const;
	};
	
}

#include "Matrix4D.tpp"