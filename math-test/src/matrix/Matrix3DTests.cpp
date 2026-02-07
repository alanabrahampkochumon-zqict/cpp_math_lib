#include <gtest/gtest.h>

#include <matrix/Matrix3D.h>
#include <vector/Vector3D.h>
#include <cstddef> 
#include <iostream>
#include <cmath>
#include <valarray>

#include "../utils/FloatEquals.h"
#include "../utils/MatrixUtils.h"

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
	EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
	EXPECT_FLOAT_EQ(0.0f, mat(0, 1));
	EXPECT_FLOAT_EQ(0.0f, mat(0, 2));

	EXPECT_FLOAT_EQ(0.0f, mat(1, 0));
	EXPECT_FLOAT_EQ(1.0f, mat(1, 1));
	EXPECT_FLOAT_EQ(0.0f, mat(1, 2));

	EXPECT_FLOAT_EQ(0.0f, mat(2, 0));
	EXPECT_FLOAT_EQ(0.0f, mat(2, 1));
	EXPECT_FLOAT_EQ(1.0f, mat(2, 2));
}

TEST(Matrix3D, InitializedWithParametersProvidesCorrectMatrix)
{
	// Arrange & Act
	const math::Matrix3D mat(
		0.0f, 1.0f, 2.0f,
		3.0f, 4.0f, 5.0f,
		6.0f, 7.0f, 8.0f
	);
	constexpr std::size_t size = 9;
	constexpr std::size_t rowMax = 3;

	// Assert
	for (size_t i = 0; i < size; ++i)
		EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

TEST(Matrix3D, InitializedWithThree3DVectorsProvidesCorrectMatrix)
{
	// Arrange & Act
	const math::Vector3D col1(0.0f, 3.0f, 6.0f);
	const math::Vector3D col2(1.0f, 4.0f, 7.0f);
	const math::Vector3D col3(2.0f, 5.0f, 8.0f);

	const math::Matrix3D<float> mat(col1, col2, col3);

	constexpr std::size_t size = 9;
	constexpr std::size_t rowMax = 3;

	// Assert
	for (size_t i = 0; i < size; ++i)
		EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

TEST(Matrix3D, CanMutateVectorAtIndex)
{
	// Arrange
	math::Matrix3D<float> mat;
	math::Vector3D<float> vec(3.0f, 1.0f, 6.0f);

	// Act
	mat[2] = vec;

	// Assert
	EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
	EXPECT_FLOAT_EQ(0.0f, mat(0, 1));
	EXPECT_FLOAT_EQ(3.0f, mat(0, 2));

	EXPECT_FLOAT_EQ(0.0f, mat(1, 0));
	EXPECT_FLOAT_EQ(1.0f, mat(1, 1));
	EXPECT_FLOAT_EQ(1.0f, mat(1, 2));

	EXPECT_FLOAT_EQ(0.0f, mat(2, 0));
	EXPECT_FLOAT_EQ(0.0f, mat(2, 1));
	EXPECT_FLOAT_EQ(6.0f, mat(2, 2));
}

TEST(Matrix3D, CanBeAccessedAsAVectorAtIndex)
{
	// Arrange
	math::Matrix3D<float> mat;

	// Act
	math::Vector3D vec = mat[1];

	// Assert
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
	EXPECT_FLOAT_EQ(0.0f, vec.z);
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
		EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

TEST(Matrix3D, CanBeAccessedAsAValueAtRowColumn)
{
	// Arrange & Act
	const math::Matrix3D mat(
		0.0f, 1.0f, 2.0f,
		3.0f, 4.0f, 5.0f,
		6.0f, 7.0f, 8.0f
	);

	constexpr std::size_t size = 9;
	constexpr std::size_t rowMax = 3;

	// Assert
	for (size_t i = 0; i < size; ++i)
		EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowMax, i % rowMax));
}

/*************************************
 *                                   *
 *         MATH OPERATIONS           *
 *                                   *
 *************************************/

TEST(Matrix3D, SumOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const math::Matrix3D b = {
		3.0f, 2.0f, 255.0f,
		-8.0f, 24.0f, 6.0f,
		7.0f, 16.0f, -98.0f
	};
	const math::Matrix3D c = {
		4.0f, 4.0f, 258.0f,
		-4.0f, 29.0f, 12.0f,
		14.0f, 8.0f, -89.0f
	};

	// Act
	const math::Matrix3D<float> res = a + b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(c(i / rowSize, i % rowSize), res(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, PlusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const math::Matrix3D b = {
		3.0f, 2.0f, 255.0f,
		-8.0f, 24.0f, 6.0f,
		7.0f, 16.0f, -98.0f
	};
	const math::Matrix3D c = {
		4.0f, 4.0f, 258.0f,
		-4.0f, 29.0f, 12.0f,
		14.0f, 8.0f, -89.0f
	};

	// Act
	a += b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(c(i / rowSize, i % rowSize), a(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, DifferenceOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const math::Matrix3D b = {
		3.0f, 2.0f, 255.0f,
		-8.0f, 24.0f, 6.0f,
		2.0f, 16.0f, -98.0f
	};
	const math::Matrix3D c = {
		-2.0f, 0.0f, -252.0f,
		12.0f, -19.0f, 0.0f,
		5.0f, -24.0f, 107.0f
	};

	// Act
	const math::Matrix3D<float> res = a - b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(c(i / rowSize, i % rowSize), res(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MinusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const math::Matrix3D<float> b = {
		3.0f, 2.0f, 255.0f,
		-8.0f, 24.0f, 6.0f,
		2.0f, 16.0f, -98.0f
	};
	const math::Matrix3D<float> c = {
		-2.0f, 0.0f, -252.0f,
		12.0f, -19.0f, 0.0f,
		5.0f, -24.0f, 107.0f
	};

	// Act
	a -= b;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(c(i / rowSize, i % rowSize), a(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesAIntegerScalarReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const int scalar = 2;

	// Act
	const math::Matrix3D<float> b = a * scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}

}

TEST(Matrix3D, IntegerScalarTimesAMatrixReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const int scalar = 2;

	// Act
	const math::Matrix3D<float> b = scalar * a;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const math::Matrix3D b = {
		2.0f, 4.0f, 6.0f,
		8.0f, 10.0f, 12.0f,
		14.0f, -16.0f, 18.0f
	};
	const int scalar = 2;

	// Act
	a *= scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(b(i / rowSize, i % rowSize), a(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesOneReturnANewMatrixWithOriginalMatrixValues)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};

	// Act
	const math::Matrix3D<float> b = a * 1;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize), b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesZeroScalarReturnsZeroMatrix)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};

	// Act
	const math::Matrix3D<float> b = a * 0;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		// Must be exactly 0.0f
		EXPECT_FLOAT_EQ(0.0f, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesAFloatScalarReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const float scalar = 2.5;

	// Act
	const math::Matrix3D<float> b = a * scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesNegativeFloatScalarFlipsSigns)
{
	// Arrange
	const math::Matrix3D a = {
		 1.0f, -2.0f,  0.0f,
		-4.0f,  5.0f, -6.0f,
		 0.0f,  8.0f,  9.0f
	};
	const float scalar = -2.0f;

	// Act
	const math::Matrix3D<float> b = a * scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize) * scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixDividedByAIntegerScalarReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const int scalar = 2;

	// Act
	const math::Matrix3D<float> b = a / scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize) / scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixDividesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};
	const math::Matrix3D b = {
		0.5f, 1.0f, 1.5f,
		2.0f, 2.5f, 3.0f,
		3.5f, -4.0f, 4.5f
	};
	const int scalar = 2;

	// Act
	a /= scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(b(i / rowSize, i % rowSize), a(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixDividedByOneReturnANewMatrixWithOriginalMatrixValues)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};

	// Act
	const math::Matrix3D<float> b = a / 1;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize), b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixDividedByZeroScalarReturnsInfinityMatrix)
{
	// Arrange
	const math::Matrix3D a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f
	};

	// Act
	const math::Matrix3D<float> b = a / 0;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		// Must be exactly 0.0f
		EXPECT_TRUE(std::isinf(b(i / rowSize, i % rowSize)));
	}
}

TEST(Matrix3D, MatrixDividedByAFloatScalarReturnsCorrectMatrix)
{
	// Arrange
	const math::Matrix3D<float> a = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0
	};
	const float scalar = 2.5;

	// Act
	const math::Matrix3D<float> b = a / scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;
	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize) / scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixDividedNegativeFloatScalarFlipsSigns)
{
	// Arrange
	const math::Matrix3D<float> a = {
		 1.0f, -2.0f,  0.0f,
		-4.0f,  5.0f, -6.0f,
		 0.0f,  8.0f,  9.0
	};
	const float scalar = -2.0f;

	// Act
	const math::Matrix3D<float> b = a / scalar;
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(a(i / rowSize, i % rowSize) / scalar, b(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesVectorReturnsANewMatrixWithCorrectValues)
{
	// Arrange
	const math::Matrix3D mat = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	const math::vec3 vec(2.0f, 1.0f, 3.0f);
	const math::vec3 expected(13.0f, 31.0f, 49.0f);

	// Act
	const math::vec3 result = mat * vec;

	// Assert
	EXPECT_FLOAT_EQ(expected.x, result.x);
	EXPECT_FLOAT_EQ(expected.y, result.y);
	EXPECT_FLOAT_EQ(expected.z, result.z);

}

TEST(Matrix3D, IdentityMatrixTimesAVectorReturnsTheSameMatrix)
{
	// Arrange
	const math::Matrix3D<float> mat;
	const math::vec3 vec(2.0f, 1.0f, 3.0f);

	// Act
	const math::vec3 result = mat * vec;

	// Assert
	EXPECT_FLOAT_EQ(vec.x, result.x);
	EXPECT_FLOAT_EQ(vec.y, result.y);
	EXPECT_FLOAT_EQ(vec.z, result.z);
}


TEST(Matrix3D, VectorTimesAMatrixReturnsANewVectorWithCorrectValues)
{
	// Arrange
	const math::Matrix3D mat = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	math::vec3 vec(2.0f, 1.0f, 3.0f);
	const math::vec3 expected(27.0f, 33.0f, 39.0f);

	// Act
	const math::vec3 result = vec * mat;

	// Assert
	EXPECT_FLOAT_EQ(expected.x, result.x);
	EXPECT_FLOAT_EQ(expected.y, result.y);
	EXPECT_FLOAT_EQ(expected.z, result.z);
}

TEST(Matrix3D, VectorTimesIdentityMatrixReturnsTheSameMatrix)
{
	// Arrange
	const math::Matrix3D<float> mat;
	math::vec3 vec(2.0f, 1.0f, 3.0f);

	// Act
	const math::vec3 result = vec * mat;

	// Assert
	EXPECT_FLOAT_EQ(vec.x, result.x);
	EXPECT_FLOAT_EQ(vec.y, result.y);
	EXPECT_FLOAT_EQ(vec.z, result.z);
}

TEST(Matrix3D, VectorTimesEqualMatrixReturnTheSameVectorWithNewValues)
{
	// Arrange
	const math::Matrix3D mat = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	math::vec3 vec(2.0f, 1.0f, 3.0f);
	const math::vec3 expected(27.0f, 33.0f, 39.0f);

	// Act
	vec *= mat;

	// Assert
	EXPECT_FLOAT_EQ(expected.x, vec.x);
	EXPECT_FLOAT_EQ(expected.y, vec.y);
	EXPECT_FLOAT_EQ(expected.z, vec.z);
}

TEST(Matrix3D, MatrixTimesMatrixGivesAnotherMatrixWithCorrectValues)
{
	// Arrange
	const math::Matrix3D mat1 = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	const math::Matrix3D mat2 = {
		2.0f, 4.0f, 6.0f,
		8.0f, 10.0f, 12.0f,
		14.0f, 16.0f, 18.0f
	};
	const math::Matrix3D expected = {
		60.0f, 72.0f, 84.0f,
		132.0f, 162.0f, 192.0f,
		204.0f, 252.0f, 300.0f
	};
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Act
	const math::Matrix3D result = mat1 * mat2;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(expected(i / rowSize, i % rowSize), result(i / rowSize, i % rowSize));
	}

}

TEST(Matrix3D, MatrixTimesIdentityMatrixReturnsSameMatrix)
{
	// Arrange
	const math::Matrix3D mat = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	const math::Matrix3D<float> eye;

	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Act
	const math::Matrix3D result = mat * eye;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(mat(i / rowSize, i % rowSize), result(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, MatrixTimesEqualAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
	// Arrange
	math::Matrix3D mat1 = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	const math::Matrix3D mat2 = {
		2.0f, 4.0f, 6.0f,
		8.0f, 10.0f, 12.0f,
		14.0f, 16.0f, 18.0f
	};
	const math::Matrix3D expected = {
		60.0f, 72.0f, 84.0f,
		132.0f, 162.0f, 192.0f,
		204.0f, 252.0f, 300.0f
	};
	constexpr std::size_t size = 9;
	constexpr std::size_t rowSize = 3;

	// Act
	mat1 *= mat2;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(expected(i / rowSize, i % rowSize), mat1(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, Matrix3DMultiplicationIsAntiCommutative)
{
	// Arrange
	const math::Matrix3D mat1 = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	const math::Matrix3D mat2 = {
		3.0f, 6.0f, 3.0f,
		12.0f, 0.0f, 2.0f,
		15.0f, 11.0f, 6.0f
	};
	constexpr std::size_t SIZE = 9;
	constexpr std::size_t ROW_SIZE = 3;

	// Act
	const math::Matrix3D result1 = mat1 * mat2;
	const math::Matrix3D result2 = mat2 * mat1;

	bool commutative = true;

	// Assert
	for (std::size_t i = 0; i < SIZE; i++)
	{
		commutative &= floatEquals(result1(i / ROW_SIZE, i % ROW_SIZE), result2(i / ROW_SIZE, i % ROW_SIZE));
	}

	EXPECT_FALSE(commutative);
}

TEST(Matrix3D, Matrix3DMultiplicationWithScalarMultiplesAreCommutative)
{
	// Arrange
	const math::Matrix3D mat1 = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	const math::Matrix3D mat2 = mat1 * 5.0f;
	constexpr std::size_t SIZE = 9;
	constexpr std::size_t ROW_SIZE = 3;

	// Act
	const math::Matrix3D result1 = mat1 * mat2;
	const math::Matrix3D result2 = mat2 * mat1;

	bool commutative = true;

	// Assert
	for (std::size_t i = 0; i < SIZE; i++)
	{
		commutative &= floatEquals(result1(i / ROW_SIZE, i % ROW_SIZE), result2(i / ROW_SIZE, i % ROW_SIZE));
	}

	EXPECT_TRUE(commutative);
}

/**
 * DETERMINANTS
 **/

TEST(Matrix3D, IdentityMatrixReturnsDeterminantOfOne)
{
	// Arrange
	const math::Matrix3D<float> mat;
	constexpr float expectedDeterminant = 1.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, DiagonalMatrixReturnsProductOfDiagonalEntriesAsDeterminant)
{
	// Arrange
	const math::Matrix3D mat(
		2.0f, 0.0f, 0.0f,
		0.0f, 3.0f, 0.0f,
		0.0f, 0.0f, 4.0f
	);
	constexpr float expectedDeterminant = 24.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, MatrixWithScalarMultipleColumnsReturnsDeterminantOfZero)
{
	const math::Matrix3D mat(
		2.0f, 1.0f, 3.0f,
		4.0f, 2.0f, 6.0f,
		1.0f, 5.0f, 4.0f
	);

	constexpr float expectedDeterminant = 0.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, MatrixWithScalarMultipleRowsReturnsDeterminantOfZero)
{
	const math::Matrix3D mat(
		2.0f, 4.0f, 3.0f,
		4.0f, 8.0f, 6.0f,
		1.0f, 2.0f, 4.0f
	);

	constexpr float expectedDeterminant = 0.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, IdentityMatrixWithSwappedRowsReturnsDeterminantOfNegativeOne)
{
	const math::Matrix3D mat(
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	);

	constexpr float expectedDeterminant = -1.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, IdentityMatrixWithSwappedColumnsReturnsDeterminantOfNegativeOne)
{
	const math::Matrix3D mat(
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	);

	constexpr float expectedDeterminant = -1.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, IdentityMatrixWithShearAppliedsReturnsDeterminantOfOne)
{
	const math::Matrix3D mat(
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	constexpr float expectedDeterminant = 1.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, MatrixDeterminantReturnsCorrectValue)
{
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 4.0f, 1.0f,
		5.0f, 6.0f, 0.0f
	);

	constexpr float expectedDeterminant = -56.0f;

	// Act
	const float actualDeterminant = mat.determinant();

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, MatrixDeterminantWithStaticWrapperReturnsCorrectValue)
{
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 4.0f, 1.0f,
		5.0f, 6.0f, 0.0f
	);

	constexpr float expectedDeterminant = -56.0f;

	// Act
	const float actualDeterminant = math::Matrix3D<float>::determinant(mat);

	// Assert
	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D, DeterminantofTransposedMatrixIsEqualToDeterminantOfTheMatrix)
{
	const math::Matrix3D a(
		1.0f, 2.0f, 3.0f,
		0.0f, 4.0f, 1.0f,
		5.0f, 6.0f, 0.0f
	);

	// Act
	const float detA = a.determinant();
	const float detAT = a.transpose().determinant();

	// Assert
	EXPECT_FLOAT_EQ(detA, detAT);
}

TEST(Matrix3D, DeterminantOfProductOfMatricesIsSameAsProductOfDeterminantOfMatrix)
{
	// det(A*B) = det(A) * det(B)
	const math::Matrix3D a(
		1.0f, 2.0f, 3.0f,
		0.0f, 4.0f, 1.0f,
		5.0f, 6.0f, 0.0f
	);
	const math::Matrix3D b(
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	);

	// Act
	const float determinantOfProduct = math::Matrix3D<float>::determinant(a * b);
	const float productOfDeterminant = a.determinant() * b.determinant();

	// Assert
	EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
}

TEST(Matrix3D, DeterminantOfAMatrixMultipledByScalarIsScalarPowNTimesTheDeterminantOfOriginalMatrix)
{
	// det(t*A) = (t^n)det(A)
	const math::Matrix3D a(
		1.0f, 2.0f, 3.0f,
		0.0f, 4.0f, 1.0f,
		5.0f, 6.0f, 0.0f
	);
	const float scalar = 5.0f;

	// Act
	const float determinantOfProduct = math::Matrix3D<float>::determinant(scalar * a);
	const float productOfDeterminant = (scalar * scalar * scalar) * a.determinant(); // n = 3 for 3x3 matrix 

	// Assert
	EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
}

TEST(Matrix3D, TransposeOfIdentityMatrixIsItself)
{
	// Arrange
	const math::Matrix3D<float> mat;

	// Act
	const math::Matrix3D<float> actual = mat.transpose();
	constexpr int size = 9;
	constexpr int rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(mat(i / rowSize, i % rowSize), actual(i / rowSize, i % rowSize));
	}
}



TEST(Matrix3D, TransposeOfAMatrixReturnsMatrixWithRowsAndColumnsSwapped)
{
	// Arrange
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 4.0f, 1.0f,
		5.0f, 6.0f, 0.0f
	);
	const math::Matrix3D expected(
		1.0f, 0.0f, 5.0f,
		2.0f, 4.0f, 6.0f,
		3.0f, 1.0f, 0.0f
	);

	// Act
	const math::Matrix3D<float> actual = mat.transpose();
	constexpr int size = 9;
	constexpr int rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(expected(i / rowSize, i % rowSize), actual(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D, TransposeOfAMatrixUsingStaticWrapperReturnsMatrixWithRowsAndColumnsSwapped)
{
	// Arrange
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 4.0f, 1.0f,
		5.0f, 6.0f, 0.0f
	);
	const math::Matrix3D expected(
		1.0f, 0.0f, 5.0f,
		2.0f, 4.0f, 6.0f,
		3.0f, 1.0f, 0.0f
	);

	// Act
	const math::Matrix3D<float> actual = math::Matrix3D<float>::transpose(mat);
	constexpr int size = 9;
	constexpr int rowSize = 3;

	// Assert
	for (std::size_t i = 0; i < size; i++)
	{
		EXPECT_FLOAT_EQ(expected(i / rowSize, i % rowSize), actual(i / rowSize, i % rowSize));
	}
}

TEST(Matrix3D_Inverse, InverseProducesAnotherMatrixWithCorrectValues)
{
	// Given
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 1.0f, 4.0f,
		5.0f, 6.0f, 0.0f
	);
	const math::Matrix3D expectedInverse(
		-24.0f, 18.0f, 5.0f,
		20.0f, -15.0f, -4.0f,
		-5.0f, 4.0f, 1.0f
	);

	// Act
	const math::Matrix3D actualInverse = mat.inverse();

	// Assert
	TestUtils::EXPECT_MAT3D_EQ(expectedInverse, actualInverse);

}

TEST(Matrix3D_Inverse, StaticWrapperForInverseReturnsAnotherMatrixWithCorrectValues)
{
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 1.0f, 4.0f,
		5.0f, 6.0f, 0.0f
	);
	const math::Matrix3D expectedInverse(
		-24.0f, 18.0f, 5.0f,
		20.0f, -15.0f, -4.0f,
		-5.0f, 4.0f, 1.0f
	);

	// Act
	const math::Matrix3D<float> actualInverse = math::Matrix3D<float>::inverse(mat);

	// Assert
	TestUtils::EXPECT_MAT3D_EQ(expectedInverse, actualInverse);
}

TEST(Matrix3D_Inverse, IdentityMatrixInverseReturnsAnotherIdentityMatrix)
{
	// Given
	const math::Matrix3D<float> identity;

	// Act
	const math::Matrix3D<float> actualInverse = identity.inverse();

	// Assert
	TestUtils::EXPECT_MAT3D_IDENTITY(actualInverse);
}

TEST(Matrix3D_Inverse, MatrixTimeInverseReturnsIdentityMatrix)
{
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 1.0f, 4.0f,
		5.0f, 6.0f, 0.0f
	);
	const math::Matrix3D<float> identity;

	// Act
	const math::Matrix3D<float> inverse = math::Matrix3D<float>::inverse(mat);
	const math::Matrix3D<float> product = mat * inverse;

	// Assert
	TestUtils::EXPECT_MAT3D_IDENTITY(product);
}

TEST(Matrix3D_Inverse, InverseTimesMatrixReturnsIdentityMatrix)
{
	const math::Matrix3D mat(
		1.0f, 2.0f, 3.0f,
		0.0f, 1.0f, 4.0f,
		5.0f, 6.0f, 0.0f
	);
	const math::Matrix3D<float> identity;

	// Act
	const math::Matrix3D<float> inverse = math::Matrix3D<float>::inverse(mat);
	const math::Matrix3D<float> product = inverse * mat;

	// Assert
	TestUtils::EXPECT_MAT3D_IDENTITY(product);
}

TEST(Matrix3D_Inverse, SingularMatrixProducesInfinityMatrix)
{
	const math::Matrix3D singularMatrix(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	);
	

	// Act
	const math::Matrix3D<float> actualInverse = math::Matrix3D<float>::inverse(singularMatrix);

	// Assert
	TestUtils::EXPECT_MAT3D_IDENTITY(actualInverse);
}

TEST(Matrix3D_Inverse, InversionOfRotationOnlyMatrixReturnsTranspose)
{
	const math::Matrix3D mat(
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);
	const math::Matrix3D transpose(
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Act
	const math::Matrix3D<float> actualInverse = math::Matrix3D<float>::inverse(mat);

	// Assert
	TestUtils::EXPECT_MAT3D_EQ(transpose, actualInverse);
}