#include <gtest/gtest.h>

#include <vector/Vector2D.h>
#include <type_traits>
/*
* INITIALIZATION AND ACCESS TESTS
*/

TEST(Vector2D, EmptyConstructorInitializesZeroVector)
{
    // Arrange & Act
    const math::Vector2D<float> vec;

    // Assert
    EXPECT_FLOAT_EQ(0.0f, vec.x);
    EXPECT_FLOAT_EQ(0.0f, vec.y);
}

TEST(Vector2D, ConstructorParametersInitializesVector)
{
    // Arrange & Act
    const math::Vector2D vec(3.0f, 1.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D, AccessibleAsXYZ)
{
    // Arrange & Act
    const math::Vector2D vec(3.0f, 1.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D, AccessibleAsSTP)
{
    // Arrange & Act
    const math::Vector2D vec(3.0f, 1.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
}

TEST(Vector2D, AccessibleAsRGB)
{
    // Arrange & Act
    const math::Vector2D vec(3.0f, 1.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
}

TEST(Vector2D, AccessibleAsArray)
{
    // Arrange & Act
    const math::Vector2D vec(3.0f, 1.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
}

TEST(Vector2D, IndexBasedAssignmentAndRetrivalSupport)
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

TEST(Vector2D, vec2Return2DFloatVector)
{
    // Arrange & Act
    constexpr bool isCorrectType = std::is_same_v<math::vec2, math::Vector2D<float>>;

    // Assert
    EXPECT_TRUE(isCorrectType);
}

TEST(Vector2D, dvec2Return2DDoubleVector)
{
    // Arrange & Act
    constexpr bool isCorrectType = std::is_same_v<math::dvec2, math::Vector2D<double>>;

    // Assert
    EXPECT_TRUE(isCorrectType);
}


/*
*  VECTOR OPERATIONS TESTS
*/

TEST(Vector2D, VectorAddition)
{
    // Arrange
    const math::Vector2D vec1(3.0f, 0.0f);
    const math::Vector2D vec2(9.0f, -5.0f);

    // Act
    const math::Vector2D result = vec1 + vec2;

    // Assert
    EXPECT_FLOAT_EQ(12.0f, result.x);
    EXPECT_FLOAT_EQ(-5.0f, result.y);
}

TEST(Vector2D, VectorPlusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
    // Arrange
    math::Vector2D vec1(3.0f, 0.0f);
    const math::Vector2D vec2(9.0f, -5.0f);

    // Act
    vec1 += vec2;

    // Assert
    EXPECT_FLOAT_EQ(12.0f, vec1.x);
    EXPECT_FLOAT_EQ(-5.0f, vec1.y);
}

TEST(Vector2D, VectorSubtraction)
{
    // Arrange
    const math::Vector2D vec1(3.0f, 0.0f);
    const math::Vector2D vec2(9.0f, -5.0f);

    // Act
    const math::Vector2D result = vec1 - vec2;

    // Assert
    EXPECT_FLOAT_EQ(-6.0f, result.x);
    EXPECT_FLOAT_EQ(5.0f, result.y);
}

TEST(Vector2D, VectorMinusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
    // Arrange
    math::Vector2D vec1(3.0f, 0.0f);
    const math::Vector2D vec2(9.0f, -5.0f);

    // Act
    vec1 -= vec2;

    // Assert
    EXPECT_FLOAT_EQ(-6.0f, vec1.x);
    EXPECT_FLOAT_EQ(5.0f, vec1.y);
}

TEST(Vector2D, ZeroVectorReturnsMagnitudeZero)
{
    // Arrange
    const math::Vector2D vec(0.0f, 0.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector2D, OneVectorReturnsMagnitudeNotEqualToOne)
{
    // Arrange
    const math::Vector2D vec(1.0f, 1.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_NE(1.0f, magnitude);
}

TEST(Vector2D, NonUnitVectorReturnsCorrectMagnitude)
{
    // Arrange
    const math::Vector2D vec(4.0f, 3.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(5.0f, magnitude);
}

TEST(Vector2D, VectorTimesZeroIsZero)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec * 0;

    // Assert
    EXPECT_FLOAT_EQ(0.0f, newVec.x);
    EXPECT_FLOAT_EQ(0.0f, newVec.y);
}

TEST(Vector2D, VectorTimesOneIsItself)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec * 1;

    // Assert
    EXPECT_FLOAT_EQ(3.0f, newVec.x);
    EXPECT_FLOAT_EQ(1.0f, newVec.y);
}

TEST(Vector2D, VectorTimesANumberIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec * 2;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, newVec.x);
    EXPECT_FLOAT_EQ(2.0f, newVec.y);
}

TEST(Vector2D, VectorTimesAFloatIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec * 2.0f;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, newVec.x);
    EXPECT_FLOAT_EQ(2.0f, newVec.y);
}

TEST(Vector2D, NumberTimesAVectorIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = 2 * vec;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, newVec.x);
    EXPECT_FLOAT_EQ(2.0f, newVec.y);
}

TEST(Vector2D, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0f, 1.0f);

    // Act
    vec *= 2;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
}

TEST(Vector2D, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0f, 1.0f);

    // Act
    vec *= 2.0;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
}


TEST(Vector2D, VectorDividedByZeroIsInfinity)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec / 0;

    // Assert
    EXPECT_FLOAT_EQ(INFINITY, newVec.x);
    EXPECT_FLOAT_EQ(INFINITY, newVec.y);
}

TEST(Vector2D, VectorDividedByOneIsItself)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec / 1;

    // Assert
    EXPECT_FLOAT_EQ(3.0f, newVec.x);
    EXPECT_FLOAT_EQ(1.0f, newVec.y);
}

TEST(Vector2D, VectorDividedByANumberIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec / 2;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, newVec.x);
    EXPECT_FLOAT_EQ(0.5f, newVec.y);
}

TEST(Vector2D, VectorDividedByAFloatIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0f, 1.0f);

    // Act
    const math::Vector2D newVec = vec / 2.0;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, newVec.x);
    EXPECT_FLOAT_EQ(0.5f, newVec.y);
}

TEST(Vector2D, VectorDividesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0f, 1.0f);

    // Act
    vec /= 2;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, vec.x);
    EXPECT_FLOAT_EQ(0.5f, vec.y);
}

TEST(Vector2D, VectorDividesEqualAFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0f, 1.0f);

    // Act
    vec /= 2.0;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, vec.x);
    EXPECT_FLOAT_EQ(0.5f, vec.y);
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
