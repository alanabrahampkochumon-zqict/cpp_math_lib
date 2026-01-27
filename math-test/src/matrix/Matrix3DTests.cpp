#include <gtest/gtest.h>

#include <matrix/Matrix3D.h>
#include <cstddef>

/*************************************
 *                                   *
 *         INITIALIZATIONS           *
 *                                   *
 *************************************
 **/

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
		0.0, 3.0, 6.0,
		1.0, 4.0, 7.0,
		2.0, 5.0, 8.0
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
	ASSERT_FLOAT_EQ(0.0f, mat(0, 2));

	ASSERT_FLOAT_EQ(0.0f, mat(1, 0));
	ASSERT_FLOAT_EQ(1.0f, mat(1, 1));
	ASSERT_FLOAT_EQ(0.0f, mat(1, 2));

	ASSERT_FLOAT_EQ(vec.x, mat(2, 0));
	ASSERT_FLOAT_EQ(vec.y, mat(2, 1));
	ASSERT_FLOAT_EQ(vec.z, mat(2, 2));
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