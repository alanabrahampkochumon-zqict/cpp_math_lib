#pragma once

#include <gtest/gtest.h>

#include <cmath>

#include <matrix/Matrix3D.h>

namespace TestUtils::Matrix3D
{
	
	static unsigned int SIZE = 9;
	static unsigned int ROW_SIZE = 3;

	template<typename T>
	void EXPECT_MAT3D_EQ(math::Matrix3D<T> expected, math::Matrix3D<T> actual)
	{
		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(expected(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
	void EXPECT_MAT3D_IDENTITY(math::Matrix3D<T> actual)
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
	void EXPECT_MAT3D_ZERO(math::Matrix3D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_FLOAT_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
		}
	}

	template<typename T>
	void EXPECT_MAT3D_INF(math::Matrix3D<T> actual)
	{

		for (unsigned int i = 0; i < SIZE; i++)
		{
			EXPECT_TRUE(std::isinf(actual(i / ROW_SIZE, i % ROW_SIZE)));
		}
	}
}
