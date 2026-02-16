#pragma once

#include <cmath>
#include <type_traits>

#include <gtest/gtest.h>

#include <vector/Vector2D.h>
#include <vector/Vector3D.h>
#include <vector/Vector4D.h>

// TODO: Template to single namespace functions
namespace TestUtils
{
	static unsigned int SIZE = 2;

	template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
	void EXPECT_VEC_EQ(math::Vector2D<T> expected, math::Vector2D<U> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				EXPECT_FLOAT_EQ(expected[i], static_cast<T>(actual[i]));
			}
			else if (std::is_same_v<T, double>)
			{
				EXPECT_DOUBLE_EQ(expected[i], static_cast<T>(actual[i]));
			}
			else
			{
				EXPECT_EQ(expected[i], static_cast<T>(actual[i]));
			}
		}
	}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void EXPECT_VEC_UNIT(math::Vector2D<T> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				EXPECT_FLOAT_EQ(T(1), static_cast<T>(actual[i]));
			}
			else if (std::is_same_v<T, double>)
			{
				EXPECT_DOUBLE_EQ(T(1), static_cast<T>(actual[i]));
			}
			else
			{
				EXPECT_EQ(T(1), static_cast<T>(actual[i]));
			}
		}
	}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void EXPECT_VEC_ZERO(math::Vector2D<T> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				EXPECT_FLOAT_EQ(T(0), static_cast<T>(actual[i]));
			}
			else if (std::is_same_v<T, double>)
			{
				EXPECT_DOUBLE_EQ(T(0), static_cast<T>(actual[i]));
			}
			else
			{
				EXPECT_EQ(T(0), static_cast<T>(actual[i]));
			}
		}
	}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void EXPECT_VEC_INF(math::Vector2D<T> actual)
	{
		EXPECT_TRUE(std::isinf(actual.x));
		EXPECT_TRUE(std::isinf(actual.y));
	}
}



// TODO: Template to single namespace functions
namespace TestUtils::Vector2D
{	
	static unsigned int SIZE = 2;

	template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
	void EXPECT_VEC_EQ(math::Vector2D<T> expected, math::Vector2D<U> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				EXPECT_FLOAT_EQ(expected[i], static_cast<T>(actual[i]));
			}
			else if (std::is_same_v<T, double>)
			{
				EXPECT_DOUBLE_EQ(expected[i], static_cast<T>(actual[i]));
			}
			else
			{
				EXPECT_EQ(expected[i], static_cast<T>(actual[i]));
			}
		}
	}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void EXPECT_VEC_UNIT(math::Vector2D<T> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				EXPECT_FLOAT_EQ(T(1), static_cast<T>(actual[i]));
			}
			else if (std::is_same_v<T, double>)
			{
				EXPECT_DOUBLE_EQ(T(1), static_cast<T>(actual[i]));
			}
			else
			{
				EXPECT_EQ(T(1), static_cast<T>(actual[i]));
			}
		}
	}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void EXPECT_VEC_ZERO(math::Vector2D<T> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				EXPECT_FLOAT_EQ(T(0), static_cast<T>(actual[i]));
			}
			else if (std::is_same_v<T, double>)
			{
				EXPECT_DOUBLE_EQ(T(0), static_cast<T>(actual[i]));
			}
			else
			{
				EXPECT_EQ(T(0), static_cast<T>(actual[i]));
			}
		}
	}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void EXPECT_VEC_INF(math::Vector2D<T> actual)
	{
		EXPECT_TRUE(std::isinf(actual.x));
		EXPECT_TRUE(std::isinf(actual.y));
	}
}

//TODO: Add Type Promotion And Checking
namespace TestUtils::Vector3D
{

	template<typename T, typename S>
	void EXPECT_VEC_EQ(math::Vector3D<T> expected, math::Vector3D<S> actual)
	{
		if constexpr (std::is_same_v<typename decltype(expected)::value_type, double> || std::is_same_v<typename decltype(actual)::value_type, double>)
		{
			EXPECT_DOUBLE_EQ(expected.x, actual.x);
			EXPECT_DOUBLE_EQ(expected.y, actual.y);
			EXPECT_DOUBLE_EQ(expected.z, actual.z);
		}
		else
		{
			EXPECT_FLOAT_EQ(expected.x, actual.x);
			EXPECT_FLOAT_EQ(expected.y, actual.y);
			EXPECT_FLOAT_EQ(expected.z, actual.z);
		}
	}

	template<typename T>
	void EXPECT_VEC_UNIT(math::Vector3D<T> actual)
	{
		if constexpr (std::is_same_v<typename decltype(actual)::value_type, double>)
		{
			EXPECT_DOUBLE_EQ(T(1), actual.x);
			EXPECT_DOUBLE_EQ(T(1), actual.y);
			EXPECT_DOUBLE_EQ(T(1), actual.z);
		}
		else
		{
			EXPECT_FLOAT_EQ(T(1), actual.z);
			EXPECT_FLOAT_EQ(T(1), actual.x);
			EXPECT_FLOAT_EQ(T(1), actual.y);
		}
	}

	template<typename T>
	void EXPECT_VEC_ZERO(math::Vector3D<T> actual)
	{
		if constexpr (std::is_same_v<typename decltype(actual)::value_type, double>)
		{
			EXPECT_DOUBLE_EQ(T(0), actual.x);
			EXPECT_DOUBLE_EQ(T(0), actual.y);
			EXPECT_DOUBLE_EQ(T(0), actual.z);
		}
		else
		{
			EXPECT_FLOAT_EQ(T(0), actual.x);
			EXPECT_FLOAT_EQ(T(0), actual.y);
			EXPECT_FLOAT_EQ(T(0), actual.z);
		}
	}

	template<typename T>
	void EXPECT_VEC_INF(math::Vector3D<T> actual)
	{
		EXPECT_TRUE(std::isinf(actual.x));
		EXPECT_TRUE(std::isinf(actual.y));
		EXPECT_TRUE(std::isinf(actual.z));
	}
}


namespace TestUtils::Vector4D
{
	template<typename T>
	void EXPECT_VEC_EQ(math::Vector4D<T> expected, math::Vector4D<T> actual)
	{
		EXPECT_FLOAT_EQ(expected.x, actual.x);
		EXPECT_FLOAT_EQ(expected.y, actual.y);
		EXPECT_FLOAT_EQ(expected.z, actual.z);
		EXPECT_FLOAT_EQ(expected.w, actual.w);
	}

	template<typename T>
	void EXPECT_VEC_UNIT(math::Vector4D<T> actual)
	{
		EXPECT_FLOAT_EQ(T(1), actual.x);
		EXPECT_FLOAT_EQ(T(1), actual.y);
		EXPECT_FLOAT_EQ(T(1), actual.z);
		EXPECT_FLOAT_EQ(T(1), actual.w);
	}

	template<typename T>
	void EXPECT_VEC_ZERO(math::Vector4D<T> actual)
	{
		EXPECT_FLOAT_EQ(T(0), actual.x);
		EXPECT_FLOAT_EQ(T(0), actual.y);
		EXPECT_FLOAT_EQ(T(0), actual.z);
		EXPECT_FLOAT_EQ(T(0), actual.w);
	}

	template<typename T>
	void EXPECT_VEC_INF(math::Vector4D<T> actual)
	{
		EXPECT_TRUE(std::isinf(actual.x));
		EXPECT_TRUE(std::isinf(actual.y));
		EXPECT_TRUE(std::isinf(actual.z));
		EXPECT_TRUE(std::isinf(actual.w));
	}

}