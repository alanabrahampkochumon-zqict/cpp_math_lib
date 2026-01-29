#include <gtest/gtest.h>

#include <matrix/Matrix3D.h>
#include <cstddef>
#include <iostream>

/*************************************
 *                                   *
 *         INITIALIZATIONS           *
 *                                   *
 *************************************/

TEST(Matrix3D, InitializedWithOutParametersProvidesIdentityMatrix)
{
	// Arrange & Act
	const math::Matrix3D<float> mat;

	// Assert
	ASSERT_FLOAT_EQ(1.0f, mat(0, 0));
	ASSERT_FLOAT_EQ(0.0f, mat(0, 1));
	ASSERT_FLOAT_EQ(0.0f, mat(0, 2));

	ASSERT_FLOAT_EQ(0.0f, mat(1, 0));
	ASSERT_FLOAT_EQ(1.0f, mat(1, 1));
	ASSERT_FLOAT_EQ(0.0f, mat(1, 2));

	ASSERT_FLOAT_EQ(0.0f, mat(2, 0));
	ASSERT_FLOAT_EQ(0.0f, mat(2, 1));
	ASSERT_FLOAT_EQ(1.0f, mat(2, 2));
}

TEST(Matrix3D, InitializedWithParametersProvidesCorrectMatrix)
{
	// Arrange & Act
	const math::Matrix3D<float> mat(
		0.0, 1.0, 2.0,
		3.0, 4.0, 5.0,
		6.0, 7.0, 8.0
	);
	constexpr std::size_t size = 9;
	constexpr std::size_t rowMax = 3;

	// Assert
	for (size_t i = 0; i < size; ++i)
		ASSERT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

TEST(Matrix3D, InitializedWithThree3DVectorsProvidesCorrectMatrix)
{
	// Arrange & Act
	const math::Vector3D col1(0.0, 3.0, 6.0);
	const math::Vector3D col2(1.0, 4.0, 7.0);
	const math::Vector3D col3(2.0, 5.0, 8.0);

	const math::Matrix3D mat(col1, col2, col3);

	constexpr std::size_t size = 9;
	constexpr std::size_t rowMax = 3;

	// Assert
	for (size_t i = 0; i < size; ++i)
		ASSERT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

TEST(Matrix3D, CanMutateVectorAtIndex)
{
	// Arrange
	math::Matrix3D<float> mat;
	math::Vector3D<float> vec(3.0, 1.0, 6.0);

	// Act
	mat[2] = vec;
	
	// Assert
	ASSERT_FLOAT_EQ(1.0f, mat(0, 0));
	ASSERT_FLOAT_EQ(0.0f, mat(0, 1));
	ASSERT_FLOAT_EQ(3.0f, mat(0, 2));

	ASSERT_FLOAT_EQ(0.0f, mat(1, 0));
	ASSERT_FLOAT_EQ(1.0f, mat(1, 1));
	ASSERT_FLOAT_EQ(1.0f, mat(1, 2));

	ASSERT_FLOAT_EQ(0.0f, mat(2, 0));
	ASSERT_FLOAT_EQ(0.0f, mat(2, 1));
	ASSERT_FLOAT_EQ(6.0f, mat(2, 2));
}

TEST(Matrix3D, CanBeAccessedAsAVectorAtIndex)
{
	// Arrange
	math::Matrix3D<float> mat;

	// Act
	math::Vector3D vec = mat[1];

	// Assert
	ASSERT_FLOAT_EQ(0.0f, vec.x);
	ASSERT_FLOAT_EQ(1.0f, vec.y);
	ASSERT_FLOAT_EQ(0.0f, vec.z);
}

TEST(Matrix3D, CanMutateValueAtRowColumn)
{
	// Arrange
	math::Matrix3D<float> mat;
	
	// Act
	constexpr std::size_t size = 9;
	constexpr std::size_t rowMax = 3;
	for (size_t i = 0; i < size; ++i)
		mat(i / rowMax, i % rowMax) = static_cast<float>(i);
	 
	// Assert
	for (size_t i = 0; i < size; ++i)
		ASSERT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

TEST(Matrix3D, CanBeAccessedAsAValueAtRowColumn)
{
	// Arrange & Act
	const math::Matrix3D<float> mat(
		0.0, 1.0, 2.0,
		3.0, 4.0, 5.0,
		6.0, 7.0, 8.0
	);

	constexpr std::size_t size = 9;
	constexpr std::size_t rowMax = 3;

	// Assert
	for (size_t i = 0; i < size; ++i)
		ASSERT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

/*************************************
 *                                   *
 *         MATH OPERATIONS           *
 *                                   *
 *************************************/

TEST(Matrix3D, SumOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const math::Matrix3D<float> b = {
		3.0, 2.0, 255.0,
		-8.0, 24.0, 6.0,
		7.0, 16.0, -98.0
	};
	const math::Matrix3D<float> c = {
		4.0, 4.0, 258.0,
		-4.0, 29.0, 12.0,
		14.0, 8.0, -89.0
	};

	// Act
	const math::Matrix3D<float> res = a + b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(c(i / rowSize, i % rowSize), res(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, PlusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const math::Matrix3D<float> b = {
		3.0, 2.0, 255.0,
		-8.0, 24.0, 6.0,
		7.0, 16.0, -98.0
	};
	const math::Matrix3D<float> c = {
		4.0, 4.0, 258.0,
		-4.0, 29.0, 12.0,
		14.0, 8.0, -89.0
	};

	// Act
	a += b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(c(i / rowSize, i % rowSize), a(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, DifferenceOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const math::Matrix3D<float> b = {
		3.0, 2.0, 255.0,
		-8.0, 24.0, 6.0,
		2.0, 16.0, -98.0
	};
	const math::Matrix3D<float> c = {
		-2.0, 0.0, -252.0,
		12.0, -19.0, 0.0,
		5.0, -24.0, 107.0
	};

	// Act
	const math::Matrix3D<float> res = a - b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(c(i / rowSize, i % rowSize), res(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MinusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const math::Matrix3D<float> b = {
		3.0, 2.0, 255.0,
		-8.0, 24.0, 6.0,
		2.0, 16.0, -98.0
	};
	const math::Matrix3D<float> c = {
		-2.0, 0.0, -252.0,
		12.0, -19.0, 0.0,
		5.0, -24.0, 107.0
	};

	// Act
	a -= b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(c(i / rowSize, i % rowSize), a(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesAIntegerScalarReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const int scalar = 2;

	// Act
	const math::Matrix3D<float> b = a * scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}

}

TEST(Matrix3D, IntegerScalarTimesAMatrixReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const int scalar = 2;

	// Act
	const math::Matrix3D<float> b = scalar * a;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const math::Matrix3D<float> b = {
		2.0, 4.0, 6.0,
		8.0, 10.0, 12.0,
		14.0, -16.0, 18.0
	};
	const int scalar = 2;

	// Act
	a *= scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(b(i / rowSize, i % rowSize), a(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesOneReturnANewMatrixWithOriginalMatrixValues)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	
	// Act
	const math::Matrix3D<float> b = a * 1;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(a(i / rowSize, i % rowSize), b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesZeroScalarReturnsZeroMatrix)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};

	// Act
	const math::Matrix3D<float> b = a * 0;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		// Must be exactly 0.0f
		ASSERT_FLOAT_EQ(0.0f, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesAFloatScalarReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, -8.0, 9.0
	};
	const float scalar = 2.5;

	// Act
	const math::Matrix3D<float> b = a * scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesNegativeFloatScalarFlipsSigns)
{
	// Arrange
	const math::Matrix3D<float> a = {
		 1.0, -2.0,  0.0,
		-4.0,  5.0, -6.0,
		 0.0,  8.0,  9.0
	};
	const float scalar = -2.0f;

	// Act
	const math::Matrix3D<float> b = a * scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}
}