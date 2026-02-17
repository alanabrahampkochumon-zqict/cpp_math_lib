#include <gtest/gtest.h>

#include <vector/Vector2D.h>
#include <type_traits>

#include "../utils/MatrixUtils.h"
#include "../utils/VectorUtils.h"
/*
* INITIALIZATION AND ACCESS TESTS
*/
using namespace TestUtils;

TEST(Vector2D_Initialization, EmptyConstructorInitializesZeroVector)
{
	// Arrange & Act
	const math::Vector2D<float> vec;

	// Assert
	EXPECT_VEC_ZERO(vec);
}

TEST(Vector2D_Initialization, IntializationWithIntegersSupported)
{
	// Arrange & Act
	const math::Vector2D vec(3, 1);

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, int>);
	EXPECT_EQ(3, vec.x);
	EXPECT_EQ(1, vec.y);
}

TEST(Vector2D_Initialization, ConstructorParametersInitializesVector)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D_Access, AccessibleAsXYZ)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D_Access, AccessibleAsSTP)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.s);
	EXPECT_FLOAT_EQ(1.0f, vec.t);
}

TEST(Vector2D_Access, AccessibleAsRGB)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.r);
	EXPECT_FLOAT_EQ(1.0f, vec.g);
}

TEST(Vector2D_Access, AccessibleAsArray)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
	EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
}

TEST(Vector2D_Access, IndexBasedAssignmentAndRetrivalSupport)
{
	// Arrange
	math::Vector2D<float> vec;

	// Act
	vec[0] = 3.0f;
	vec[1] = 1.0f;

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec[0]);
	EXPECT_FLOAT_EQ(1.0f, vec[1]);

}

TEST(Vector2D_Access, vec2Return2DFloatVector)
{
	// Arrange & Act
	constexpr bool isCorrectType = std::is_same_v<math::vec2, math::Vector2D<float>>;

	// Assert
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector2D_Access, dvec2Return2DDoubleVector)
{
	// Arrange & Act
	constexpr bool isCorrectType = std::is_same_v<math::dvec2, math::Vector2D<double>>;

	// Assert
	EXPECT_TRUE(isCorrectType);
}


/*
*  VECTOR OPERATIONS TESTS
*/

TEST(Vector2D_Addition, VectorPlusVectorReturnsCorrectVector)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(12.0f, -5.0f);

	// Act
	const math::Vector2D result = vec1 + vec2;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Addition, VectorPlusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(12.0f, -5.0f);

	// Act
	vec1 += vec2;

	// Assert
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Addition, VectorPlusVectorOfDifferentTypesReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(12.0, -5.0);

	// Act
	const math::Vector2D result = vec1 + vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Addition, VectorPlusEqualsVectorOfDifferentTypesReturnsVectorWithTypePromotion)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(12.0f, -5.0f);

	// Act
	vec1 += vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Subraction, VectorMinusVectorReturnsCorrectVector)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(-6.0f, 5.0f);

	// Act
	const math::Vector2D result = vec1 - vec2;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Subraction, VectorMinusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(-6.0f, 5.0f);

	// Act
	vec1 -= vec2;

	// Assert
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Subraction, VectorMinusVectorOfDifferentTypeReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(-6.0, 5.0);

	// Act
	const math::Vector2D result = vec1 - vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Subraction, VectorMinusEqualsAnotherVectorWithDifferentTypeReturnsFirstVectorWithoutTypePromotion)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(-6.0f, 5.0f);

	// Act
	vec1 -= vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Mutliplication, VectorTimesZeroIsZero)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec * 0;

	// Assert
	EXPECT_VEC_ZERO(result);
}

TEST(Vector2D_Mutliplication, VectorTimesOneIsItself)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec * 1;

	// Assert
	EXPECT_VEC_EQ(vec, result);
}

TEST(Vector2D_Mutliplication, VectorTimesANumberIsANewVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = vec * 2;

	// Assert
	EXPECT_VEC_EQ(expected, result);

}

TEST(Vector2D_Mutliplication, VectorTimesAFloatIsANewVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = vec * 2.0f;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Mutliplication, NumberTimesAVectorIsANewVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = 2 * vec;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Mutliplication, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	vec *= 2;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Mutliplication, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	vec *= 2.0;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Mutliplication, VectorTimesEqualADoubleScalarIsSameVectorWithoutTypePromotion)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	vec *= 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Mutliplication, FloatVectorTimesADoubleScalarReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = vec * 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Mutliplication, IntegerVectorTimesEqualADoubleScalarReturnsVectorWithMinimalPrecisionLoss)
{
	// Arrange
	math::Vector2D vec(3, 1);
	const math::Vector2D expected(7, 2);

	// Act
	vec *= 2.5;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, int>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividedByZeroIsInfinityVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec / 0;

	// Assert
	EXPECT_VEC_INF(result);
}

TEST(Vector2D_Division, VectorDividedReturnsVectorWithSameValues)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec / 1;

	// Assert
	EXPECT_VEC_EQ(vec, result);
}

TEST(Vector2D_Division, VectorDividedByANumberReturnsANewVectorWithCorrectValues)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	const math::Vector2D result = vec / 2;

	// Assert
	EXPECT_VEC_EQ(expected, result);

}

TEST(Vector2D_Division, VectorDividedByAFloatReturnsANewVectorWithCorrectValues)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	const math::Vector2D result = vec / 2.0f;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Division, VectorDividesEqualAScalarIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	vec /= 2;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividesEqualAFloatIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	vec /= 2.0;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividesEqualADoubleIsSameVectorWithoutTypePromotion)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	vec /= 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividedByADoubleReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	const math::Vector2D result = vec / 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Division, IntegerVectorDivideEqualsAFloatReturnsVectorWithMinimalPrecisionLoss)
{
	// Arrange
	math::Vector2D vec(3, 1);
	const math::Vector2D expected(12, 4);

	// Act
	vec /= 0.25f;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, int>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Magnitude, ZeroVectorReturnsMagnitudeZero)
{
	// Arrange
	const math::Vector2D vec(0.0f, 0.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector2D_Magnitude, OneVectorReturnsMagnitudeNotEqualToOne)
{
	// Arrange
	const math::Vector2D vec(1.0f, 1.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_NE(1.0f, magnitude);
}

TEST(Vector2D_Magnitude, NonUnitVectorReturnsCorrectMagnitude)
{
	// Arrange
	const math::Vector2D vec(4.0f, 3.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_FLOAT_EQ(5.0f, magnitude);
}


TEST(Vector2D, VectorWhenNormalizedReturnsANormalVector)
{
	// Arrange
	math::Vector2D vec(4.0f, 3.0f);

	// Act
	math::Vector2D normalized = vec.normalize();

	// Assert
	EXPECT_FLOAT_EQ(0.8f, normalized.x);
	EXPECT_FLOAT_EQ(0.6f, normalized.y);
}

// Dot Product
TEST(Vector2D, VectorWhenDotWithItselfReturnsOne)
{
	// Arrange
	const math::Vector2D vec(1.0f, 0.0f);

	// Act
	const float res = vec.dot(vec);

	// Assert
	EXPECT_FLOAT_EQ(1.0, res);
}

TEST(Vector2D, VectorWhenDotWithOrthogonalVectorReturnZero)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 0.0f);
	const math::Vector2D vec2(0.0f, 1.0f);

	// Act
	const float res = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(0.0, res);
}

TEST(Vector2D, VectorWhenDotWithOppositeParallelVectorReturnsNegativeOne)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 0.0f);
	const math::Vector2D vec2(-1.0f, 0.0f);

	// Act
	const float res = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(-1.0, res);
}

TEST(Vector2D, VectorWhenDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 2.0f);
	const math::Vector2D vec2(4.0f, -5.0f);

	// Act
	const float res = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(-6.0, res);
}

TEST(Vector2D, VectorWhenStaticWrapperDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 2.0f);
	const math::Vector2D vec2(4.0f, -5.0f);

	// Act
	const float res = math::Vector2D<float>::dot(vec1, vec2);

	// Assert
	EXPECT_FLOAT_EQ(-6.0, res);
}

TEST(Vector2D, UnitXVectorWhenCrossWithUnitYVectorReturnsOne)
{
	// Arrange
	math::Vector2D vec1(1.0f, 0.0f);
	math::Vector2D vec2(0.0f, 1.0f);

	// Act
	const float res = vec1.cross(vec2);

	// Assert
	EXPECT_FLOAT_EQ(1.0, res);
}

TEST(Vector2D, UnitYVectorWhenCrossWithUnitXVectorReturnsUnitNegativeOne)
{
	// Arrange
	const math::Vector2D vec1(0.0f, 1.0f);
	const math::Vector2D vec2(1.0f, 0.0f);

	// Act
	float res = vec1.cross(vec2);

	// Assert
	EXPECT_FLOAT_EQ(-1.0f, res);
}

TEST(Vector2D, UnitVectorCrossWithItselfReturnZero)
{
	// Arrange
	const math::Vector2D vec(0.0f, 1.0f);


	// Act
	const float res = vec.cross(vec);

	// Assert
	EXPECT_FLOAT_EQ(0.0f, res);
}

TEST(Vector2D, VectorCrossWithAnotherNonParallelVectorReturnsPseudoCrossProduct)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(0.0f, 4.0f);

	// Act
	const float res = vec1.cross(vec2);

	// Assert
	EXPECT_FLOAT_EQ(12.0f, res);
}

TEST(Vector2D, VectorCrossStaticWrapperWithAnotherNonParallelVectorReturnsPseudoCrossProduct)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(0.0f, 4.0f);

	// Act
	const float res = math::Vector2D<float>::cross(vec1, vec2);

	// Assert
	EXPECT_FLOAT_EQ(12.0f, res);
}

TEST(Vector2D, ParallelVectorsWhenProjectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(3.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, PerpendicularVectorsWhenProjectedReturnsZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(0.0f, 1.0f);
	const math::Vector2D expectedProjection(0.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, VectorsWhenProjectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(2.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, VectorsWhenProjectedOntoNormalizedVectorReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 4.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(3.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b, true);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, VectorsWhenProjectedUsingStaticWrapperReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(2.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = math::Vector2D<float>::project(a, b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}


TEST(Vector2D, ParallelVectorsWhenRejectedReturnsZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, PerpendicularVectorsWhenRejectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(0.0f, 1.0f);
	const math::Vector2D expectedProjection(3.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, VectorsWhenRejectedReturnNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 2.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, VectorsWhenRejectedOntoNormalizedVectorReturnNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 4.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 4.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b, true);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}

TEST(Vector2D, VectorsWhenProjectedUsingStaticWrapperReturnNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 2.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}
