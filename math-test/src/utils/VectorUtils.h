#pragma once

#include <gtest/gtest.h>
#include <cmath>

#include <vector/Vector2D.h>
#include <vector/Vector3D.h>
#include <vector/Vector4D.h>

namespace TestUtils::Vector2D
{
	template<typename T>
	void EXPECT_VEC_EQ(math::Vector2D<T> expected, math::Vector2D<T> actual)
	{
		EXPECT_FLOAT_EQ(expected.x, actual.x);
		EXPECT_FLOAT_EQ(expected.y, actual.y);
	}

	template<typename T>
	void EXPECT_VEC_UNIT(math::Vector2D<T> actual)
	{
		EXPECT_FLOAT_EQ(T(1), actual.x);
		EXPECT_FLOAT_EQ(T(1), actual.y);
	}

	template<typename T>
	void EXPECT_VEC_ZERO(math::Vector2D<T> actual)
	{
		EXPECT_FLOAT_EQ(T(0), actual.x);
		EXPECT_FLOAT_EQ(T(0), actual.y);
	}

	template<typename T>
	void EXPECT_VEC_INF(math::Vector2D<T> actual)
	{
		EXPECT_TRUE(std::isinf(actual.x));
		EXPECT_TRUE(std::isinf(actual.y));
	}
}

namespace TestUtils::Vector3D
{

	template<typename T>
	void EXPECT_VEC_EQ(math::Vector3D<T> expected, math::Vector3D<T> actual)
	{
		EXPECT_FLOAT_EQ(expected.x, actual.x);
		EXPECT_FLOAT_EQ(expected.y, actual.y);
		EXPECT_FLOAT_EQ(expected.z, actual.z);
	}

	template<typename T>
	void EXPECT_VEC_UNIT(math::Vector3D<T> actual)
	{
		EXPECT_FLOAT_EQ(T(1), actual.x);
		EXPECT_FLOAT_EQ(T(1), actual.y);
		EXPECT_FLOAT_EQ(T(1), actual.z);
	}

	template<typename T>
	void EXPECT_VEC_ZERO(math::Vector3D<T> actual)
	{
		EXPECT_FLOAT_EQ(T(0), actual.x);
		EXPECT_FLOAT_EQ(T(0), actual.y);
		EXPECT_FLOAT_EQ(T(0), actual.z);
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