#pragma once

#include <cmath>
#include <type_traits>

#include <gtest/gtest.h>

namespace TestUtils
{
	template<math::IsVector T, math::IsVector U>
	void EXPECT_VEC_EQ(T expected, U actual)
	{
		using ValueType = T::value_type;

		static_assert(T::dimension == U::dimension, "Vectors must have the same dimension (e.g. both 3D)");

		constexpr std::size_t elementCount = T::dimension;

		for (std::size_t i = 0; i < elementCount; ++i)
		{
			if constexpr (std::is_same_v<ValueType, float>)
			{
				EXPECT_FLOAT_EQ(expected[i], static_cast<ValueType>(actual[i]));
			}
			else if constexpr (std::is_same_v<ValueType, double>)
			{
				EXPECT_DOUBLE_EQ(expected[i], static_cast<ValueType>(actual[i]));
			}
			else
			{
				EXPECT_EQ(expected[i], static_cast<ValueType>(actual[i]));
			}
		}
	}

	template <math::IsVector T>
	void EXPECT_VEC_UNIT(T vector)
	{
		using ValueType = T::value_type;
		ValueType expected = ValueType(1);

		constexpr std::size_t elementCount = T::dimension;

		for (std::size_t i = 0; i < elementCount; ++i)
		{
			if constexpr (std::is_same_v<ValueType, float>)
			{
				EXPECT_FLOAT_EQ(expected, static_cast<ValueType>(vector[i]));
			}
			else if (std::is_same_v<ValueType, double>)
			{
				EXPECT_DOUBLE_EQ(expected, static_cast<ValueType>(vector[i]));
			}
			else
			{
				EXPECT_EQ(expected, static_cast<ValueType>(vector[i]));
			}
		}
	}

	template <math::IsVector T>
	void EXPECT_VEC_ZERO(T vector)
	{
		using ValueType = T::value_type;
		ValueType expected = ValueType(0);

		constexpr std::size_t elementCount = T::dimension;

		for (std::size_t i = 0; i < elementCount; ++i)
		{
			if constexpr (std::is_same_v<ValueType, float>)
			{
				EXPECT_FLOAT_EQ(expected, static_cast<ValueType>(vector[i]));
			}
			else if (std::is_same_v<ValueType, double>)
			{
				EXPECT_DOUBLE_EQ(expected, static_cast<ValueType>(vector[i]));
			}
			else
			{
				EXPECT_EQ(expected, static_cast<ValueType>(vector[i]));
			}
		}
	}

	template<math::IsVector T>
	void EXPECT_VEC_INF(T vector)
	{
		constexpr std::size_t elementCount = T::dimension;

		for (std::size_t i = 0; i < elementCount; ++i)
		{
			EXPECT_TRUE(std::isinf(vector[i]));
		}
	}
}