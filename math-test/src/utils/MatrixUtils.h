#pragma once

#include <gtest/gtest.h>

#include <cmath>

#include <matrix/Matrix3D.h>
#include <matrix/Matrix2D.h>

namespace TestUtils::Matrix3D
{
	
	static unsigned int SIZE = 9;
	static unsigned int ROW_SIZE = 3;

	template<typename T>
	void EXPECT_MAT_EQ(math::Matrix3D<T> expected, math::Matrix3D<T> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(expected(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
	void EXPECT_MAT_IDENTITY(math::Matrix3D<T> actual)
	{
		const math::Matrix3D<T> identity(
			T(1), T(0), T(0),
			T(0), T(1), T(0),
			T(0), T(0), T(1)
		);

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(identity(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
	void EXPECT_MAT_ZERO(math::Matrix3D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
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
		const math::Matrix2D<T> identity(
			T(1), T(0),
			T(0), T(1)
		);

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(identity(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE));
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
