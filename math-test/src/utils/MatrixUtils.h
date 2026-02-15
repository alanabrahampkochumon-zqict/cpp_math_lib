#pragma once

#include <gtest/gtest.h>

#include <cmath>

#include <matrix/Matrix3D.h>
#include <matrix/Matrix2D.h>

namespace TestUtils::Matrix3D
{

	static unsigned int SIZE = 9;
	static unsigned int ROW_SIZE = 3;

	template<typename T, typename S, typename = std::enable_if_t < std::is_arithmetic_v<T>>, typename = std::enable_if_t < std::is_arithmetic_v<S>>>
	void EXPECT_MAT_EQ(math::Matrix3D<T> expected, math::Matrix3D<S> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_DOUBLE_EQ(expected(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}
	// TODO: Add checks for precision

	template<typename T, typename S, typename = std::enable_if_t < std::is_arithmetic_v<T>>, typename = std::enable_if_t < std::is_arithmetic_v<S>>>
	void EXPECT_MAT_NEAR(math::Matrix3D<T> expected, math::Matrix3D<S> actual, double tolerance = 1e-5)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_NEAR(expected(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE), tolerance);
		}
	}

	template<typename T, typename = std::enable_if_t <std::is_arithmetic_v<T>>>
	void EXPECT_MAT_IDENTITY(math::Matrix3D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_DOUBLE_EQ(i / ROW_SIZE ==i % ROW_SIZE, actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T, typename = std::enable_if_t <std::is_arithmetic_v<T>>>
	void EXPECT_MAT_ZERO(math::Matrix3D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_DOUBLE_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T, typename = std::enable_if_t <std::is_arithmetic_v<T>>>
	void EXPECT_MAT_INF(math::Matrix3D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_TRUE(std::isinf(actual(i / ROW_SIZE, i % ROW_SIZE)));
		}
	}
}

namespace TestUtils::Matrix2D
{

	static unsigned int SIZE = 4;
	static unsigned int ROW_SIZE = 2;

	template<typename T>
	void EXPECT_MAT_EQ(math::Matrix2D<T> expected, math::Matrix2D<T> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(expected(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
	void EXPECT_MAT_IDENTITY(math::Matrix2D<T> actual)
	{


		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(i / ROW_SIZE == i % ROW_SIZE, actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
	void EXPECT_MAT_ZERO(math::Matrix2D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
	void EXPECT_MAT_INF(math::Matrix2D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_TRUE(std::isinf(actual(i / ROW_SIZE, i % ROW_SIZE)));
		}
	}
}
