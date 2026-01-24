#include <gtest/gtest.h>

#include <Vector2D.h>

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
    const math::Vector2D vec(3.0, 1.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D, AccessibleAsXYZ)
{
    // Arrange & Act
    const math::Vector2D vec(3.0, 1.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D, AccessibleAsSTP)
{
    // Arrange & Act
    const math::Vector2D vec(3.0, 1.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
}

TEST(Vector2D, AccessibleAsRGB)
{
    // Arrange & Act
    const math::Vector2D vec(3.0, 1.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
}

TEST(Vector2D, AccessibleAsArray)
{
    // Arrange & Act
    const math::Vector2D vec(3.0, 1.0);

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

/*
    VECTOR OPERATIONS TESTS
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

TEST(Vector2D, UnitVectorReturnsMagnitudeNotEqualToOne)
{
    // Arrange
    const math::Vector2D<float> vec;

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
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec * 0;

    // Assert
    ASSERT_FLOAT_EQ(0.0f, newVec.x);
    ASSERT_FLOAT_EQ(0.0f, newVec.y);
}

TEST(Vector2D, VectorTimesOneIsItself)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec * 1;

    // Assert
    ASSERT_FLOAT_EQ(3.0f, newVec.x);
    ASSERT_FLOAT_EQ(1.0f, newVec.y);
}

TEST(Vector2D, VectorTimesANumberIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec * 2;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
}

TEST(Vector2D, VectorTimesAFloatIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec * 2.0;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
}

TEST(Vector2D, NumberTimesAVectorIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = 2 * vec;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
}

TEST(Vector2D, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0, 1.0);

    // Act
    vec *= 2;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, vec.x);
    ASSERT_FLOAT_EQ(2.0f, vec.y);
}

TEST(Vector2D, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0, 1.0);

    // Act
    vec *= 2.0;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, vec.x);
    ASSERT_FLOAT_EQ(2.0f, vec.y);
}


TEST(Vector2D, VectorDividedByZeroIsInfinity)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec / 0;

    // Assert
    ASSERT_FLOAT_EQ(INFINITY, newVec.x);
    ASSERT_FLOAT_EQ(INFINITY, newVec.y);
}

TEST(Vector2D, VectorDividedByOneIsItself)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec / 1;

    // Assert
    ASSERT_FLOAT_EQ(3.0f, newVec.x);
    ASSERT_FLOAT_EQ(1.0f, newVec.y);
}

TEST(Vector2D, VectorDividedByANumberIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec / 2;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, newVec.x);
    ASSERT_FLOAT_EQ(0.5f, newVec.y);
}

TEST(Vector2D, VectorDividedByAFloatIsANewVector)
{
    // Arrange
    const math::Vector2D vec(3.0, 1.0);

    // Act
    const math::Vector2D newVec = vec / 2.0;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, newVec.x);
    ASSERT_FLOAT_EQ(0.5f, newVec.y);
}

TEST(Vector2D, VectorDividesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0, 1.0);

    // Act
    vec /= 2;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, vec.x);
    ASSERT_FLOAT_EQ(0.5f, vec.y);
}

TEST(Vector2D, VectorDividesEqualAFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector2D vec(3.0, 1.0);

    // Act
    vec /= 2.0;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, vec.x);
    ASSERT_FLOAT_EQ(0.5f, vec.y);
}


TEST(Vector2D, VectorWhenNormalizedReturnsANormalVector)
{
    // Arrange
    math::Vector2D vec(4.0, 3.0);

    // Act
    math::Vector2D normalized = vec.normalize();

    // Assert
    ASSERT_FLOAT_EQ(0.8f, normalized.x);
    ASSERT_FLOAT_EQ(0.6f, normalized.y);
}

// Dot Product
TEST(Vector2D, VectorWhenDotWithItselfReturnsOne)
{
    // Arrange
    const math::Vector2D<float> vec(1.0, 0.0);

    // Act
    const float res = vec.dot(vec);

    // Assert
    ASSERT_FLOAT_EQ(1.0, res);
}

TEST(Vector2D, VectorWhenDotWithOrthogonalVectorReturnZero)
{
    // Arrange
    const math::Vector2D<float> vec1(1.0, 0.0);
    const math::Vector2D<float> vec2(0.0, 1.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(0.0, res);
}

TEST(Vector2D, VectorWhenDotWithOppositeParallelVectorReturnsNegativeOne)
{
    // Arrange
    const math::Vector2D<float> vec1(1.0, 0.0);
    const math::Vector2D<float> vec2(-1.0, 0.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(-1.0, res);
}

TEST(Vector2D, VectorWhenDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
    // Arrange
    const math::Vector2D<float> vec1(1.0, 2.0);
    const math::Vector2D<float> vec2(4.0, -5.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(-6.0, res);
}

TEST(Vector2D, VectorWhenStaticWrapperDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
    // Arrange
    const math::Vector2D<float> vec1(1.0, 2.0);
    const math::Vector2D<float> vec2(4.0, -5.0);

    // Act
    const float res = math::Vector2D<float>::dot(vec1, vec2);

    // Assert
    ASSERT_FLOAT_EQ(-6.0, res);
}

TEST(Vector2D, UnitXVectorWhenCrossWithUnitYVectorReturnsOne)
{
    // Arrange
    math::Vector2D<float> vec1(1.0, 0.0);
    math::Vector2D<float> vec2(0.0, 1.0);

    // Act
    const float res = vec1.cross(vec2);

    // Assert
    ASSERT_FLOAT_EQ(1.0, res);
}

TEST(Vector2D, UnitYVectorWhenCrossWithUnitXVectorReturnsUnitNegativeOne)
{
    // Arrange
    const math::Vector2D<float> vec1(0.0, 1.0);
    const math::Vector2D<float> vec2(1.0, 0.0);

    // Act
    float res = vec1.cross(vec2);

    // Assert
    ASSERT_FLOAT_EQ(-1.0, res);
}

TEST(Vector2D, UnitVectorCrossWithItselfReturnZero)
{
    // Arrange
    const math::Vector2D<float> vec(0.0, 1.0);


    // Act
    const float res = vec.cross(vec);

    // Assert
    ASSERT_FLOAT_EQ(0.0, res);
}

TEST(Vector2D, VectorCrossWithAnotherNonParallelVectorReturnsPseudoCrossProduct)
{
    // Arrange
    const math::Vector2D<float> vec1(3.0, 0.0);
    const math::Vector2D<float> vec2(0.0, 4.0);

    // Act
    const float res = vec1.cross(vec2);

    // Assert
    ASSERT_FLOAT_EQ(12.0, res);
}

TEST(Vector2D, VectorCrossStaticWrapperWithAnotherNonParallelVectorReturnsPseudoCrossProduct)
{
    // Arrange
    const math::Vector2D<float> vec1(3.0, 0.0);
    const math::Vector2D<float> vec2(0.0, 4.0);

    // Act
    const float res = math::Vector2D<float>::cross(vec1, vec2);

    // Assert
    ASSERT_FLOAT_EQ(12.0, res);
}