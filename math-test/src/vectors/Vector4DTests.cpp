#include <gtest/gtest.h>

#include <Vector4D.h>

/*
* INITIALIZATION AND ACCESS TESTS
*/

TEST(Vector4D, EmptyConstructorInitializesZeroVector)
{
    // Arrange & Act
    const math::Vector4D<float> vec;

    // Assert
    EXPECT_FLOAT_EQ(0.0f, vec.x);
    EXPECT_FLOAT_EQ(0.0f, vec.y);
    EXPECT_FLOAT_EQ(0.0f, vec.z);
}

TEST(Vector4D, ConstructorParametersInitializesVector)
{
    // Arrange & Act
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector4D, AccessibleAsXYZ)
{
    // Arrange & Act
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector4D, AccessibleAsSTP)
{
    // Arrange & Act
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
}

TEST(Vector4D, AccessibleAsRGB)
{
    // Arrange & Act
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
}

TEST(Vector4D, AccessibleAsArray)
{
    // Arrange & Act
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
}

TEST(Vector4D, IndexBasedAssignmentAndRetrivalSupport)
{
    // Arrange
    math::Vector4D<float> vec;

    // Act
    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    
    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);

}

TEST(Vector4D, vec3Return3DFloatVector)
{
    // Arrange & Act
    constexpr bool isCorrectType = std::is_same_v<math::vec3, math::Vector4D<float>>;

    // Assert
    EXPECT_TRUE(isCorrectType);
}

TEST(Vector4D, dvec3Return3DDoubleVector)
{
    // Arrange & Act
    constexpr bool isCorrectType = std::is_same_v<math::dvec3, math::Vector4D<double>>;

    // Assert
    EXPECT_TRUE(isCorrectType);
}

/*
*   VECTOR OPERATIONS TESTS
*/

TEST(Vector4D, VectorAddition)
{
    // Arrange
    const math::Vector4D vec1(3.0f, 0.0f, -1.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f);

    // Act
    const math::Vector4D result = vec1 + vec2;

    // Assert
    EXPECT_FLOAT_EQ(12.0f, result.x);
    EXPECT_FLOAT_EQ(-5.0f, result.y);
    EXPECT_FLOAT_EQ(9.0f, result.z);
}

TEST(Vector4D, VectorPlusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
    // Arrange
    math::Vector4D vec1(3.0f, 0.0f, -1.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f);

    // Act
   vec1 += vec2;

    // Assert
    EXPECT_FLOAT_EQ(12.0f, vec1.x);
    EXPECT_FLOAT_EQ(-5.0f, vec1.y);
    EXPECT_FLOAT_EQ(9.0f, vec1.z);
}

TEST(Vector4D, VectorSubtraction)
{
    // Arrange
    const math::Vector4D vec1(3.0f, 0.0f, -1.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f);

    // Act
    const math::Vector4D result = vec1 - vec2;

    // Assert
    EXPECT_FLOAT_EQ(-6.0f, result.x);
    EXPECT_FLOAT_EQ(5.0f, result.y);
    EXPECT_FLOAT_EQ(-11.0f, result.z);
}

TEST(Vector4D, VectorMinusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
    // Arrange
    math::Vector4D vec1(3.0f, 0.0f, -1.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f);

    // Act
    vec1 -= vec2;

    // Assert
    EXPECT_FLOAT_EQ(-6.0f, vec1.x);
    EXPECT_FLOAT_EQ(5.0f, vec1.y);
    EXPECT_FLOAT_EQ(-11.0f, vec1.z);
}

TEST(Vector4D, ZeroVectorReturnsMagnitudeZero)
{
    // Arrange
    const math::Vector4D vec(0.0f, 0.0f, 0.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector4D, UnitVectorReturnsMagnitudeNotEqualToOne)
{
    // Arrange
    const math::Vector4D<float> vec;

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_NE(1.0f, magnitude);
}

TEST(Vector4D, NonUnitVectorReturnsCorrectMagnitude)
{
    // Arrange
    const math::Vector4D vec(2.0f, 3.0f, 6.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(7.0f, magnitude);
}

TEST(Vector4D, VectorTimesZeroIsZero)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec * 0;

    // Assert
    ASSERT_FLOAT_EQ(0.0f, newVec.x);
    ASSERT_FLOAT_EQ(0.0f, newVec.y);
    ASSERT_FLOAT_EQ(0.0f, newVec.z);
}

TEST(Vector4D, VectorTimesOneIsItself)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec * 1;

    // Assert
    ASSERT_FLOAT_EQ(3.0f, newVec.x);
    ASSERT_FLOAT_EQ(1.0f, newVec.y);
    ASSERT_FLOAT_EQ(6.0f, newVec.z);
}

TEST(Vector4D, VectorTimesANumberIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec * 2;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
    ASSERT_FLOAT_EQ(12.0f, newVec.z);
}

TEST(Vector4D, VectorTimesAFloatIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec * 2.0;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
    ASSERT_FLOAT_EQ(12.0f, newVec.z);
}

TEST(Vector4D, NumberTimesAVectorIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = 2 * vec;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
    ASSERT_FLOAT_EQ(12.0f, newVec.z);
}

TEST(Vector4D, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    vec *= 2;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, vec.x);
    ASSERT_FLOAT_EQ(2.0f, vec.y);
    ASSERT_FLOAT_EQ(12.0f, vec.z);
}

TEST(Vector4D, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    vec *= 2.0;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, vec.x);
    ASSERT_FLOAT_EQ(2.0f, vec.y);
    ASSERT_FLOAT_EQ(12.0f, vec.z);
}


TEST(Vector4D, VectorDividedByZeroIsInfinity)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec / 0;

    // Assert
    ASSERT_FLOAT_EQ(INFINITY, newVec.x);
    ASSERT_FLOAT_EQ(INFINITY, newVec.y);
    ASSERT_FLOAT_EQ(INFINITY, newVec.z);
}

TEST(Vector4D, VectorDividedByOneIsItself)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec / 1;

    // Assert
    ASSERT_FLOAT_EQ(3.0f, newVec.x);
    ASSERT_FLOAT_EQ(1.0f, newVec.y);
    ASSERT_FLOAT_EQ(6.0f, newVec.z);
}

TEST(Vector4D, VectorDividedByANumberIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec / 2;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, newVec.x);
    ASSERT_FLOAT_EQ(0.5f, newVec.y);
    ASSERT_FLOAT_EQ(3.0f, newVec.z);
}

TEST(Vector4D, VectorDividedByAFloatIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    const math::Vector4D newVec = vec / 2.0;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, newVec.x);
    ASSERT_FLOAT_EQ(0.5f, newVec.y);
    ASSERT_FLOAT_EQ(3.0f, newVec.z);
}

TEST(Vector4D, VectorDividesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    vec /= 2;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, vec.x);
    ASSERT_FLOAT_EQ(0.5f, vec.y);
    ASSERT_FLOAT_EQ(3.0f, vec.z);
}

TEST(Vector4D, VectorDividesEqualAFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0, 1.0, 6.0);

    // Act
    vec /= 2.0;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, vec.x);
    ASSERT_FLOAT_EQ(0.5f, vec.y);
    ASSERT_FLOAT_EQ(3.0f, vec.z);
}


TEST(Vector4D, VectorWhenNormalizedReturnsANormalVector)
{
    // Arrange
    const math::Vector4D vec(0.0, 3.0, 4.0);

    // Act
    const math::Vector4D normalized = vec.normalize();

    // Assert
    ASSERT_FLOAT_EQ(0.0f, normalized.x);
    ASSERT_FLOAT_EQ(0.6f, normalized.y);
    ASSERT_FLOAT_EQ(0.8f, normalized.z);
}

// Dot Product
TEST(Vector4D, VectorWhenDotWithItselfReturnsOne)
{
	// Arrange
    const math::Vector4D<float> vec(1.0, 0.0, 0.0);

    // Act
    const float res = vec.dot(vec);

    // Assert
    ASSERT_FLOAT_EQ(1.0, res);
}

TEST(Vector4D, VectorWhenDotWithOrthogonalVectorReturnZero)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 0.0, 0.0);
    const math::Vector4D<float> vec2(0.0, 1.0, 0.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(0.0, res);
}

TEST(Vector4D, VectorWhenDotWithOppositeParallelVectorReturnsNegativeOne)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 0.0, 0.0);
    const math::Vector4D<float> vec2(-1.0, 0.0, 0.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(-1.0, res);
}

TEST(Vector4D, VectorWhenDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 2.0, 3.0);
    const math::Vector4D<float> vec2(4.0, -5.0, 6.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(12.0, res);
}

TEST(Vector4D, VectorWhenStaticWrapperDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 2.0, 3.0);
    const math::Vector4D<float> vec2(4.0, -5.0, 6.0);

    // Act
    const float res = math::Vector4D<float>::dot(vec1, vec2);

    // Assert
    ASSERT_FLOAT_EQ(12.0, res);
}

TEST(Vector4D, UnitXVectorWhenCrossWithUnitYVectorReturnsUnitZVector)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 0.0, 0.0);
    const math::Vector4D<float> vec2(0.0, 1.0, 0.0);

    const math::Vector4D<float> res(0.0, 0.0, 1.0);
    
	// Act
    const math::Vector4D<float> ret = vec1.cross(vec2);

    // Assert
    for (int i = 0; i < 3; i++)
    {
        ASSERT_FLOAT_EQ(res[i], ret[i]);
    }
    
}

TEST(Vector4D, UnitYVectorWhenCrossWithUnitXVectorReturnsUnitNegativeZVector)
{
    // Arrange
    const math::Vector4D<float> vec1(0.0, 1.0, 0.0);
    const math::Vector4D<float> vec2(1.0, 0.0, 0.0);

    const math::Vector4D<float> res(0.0, 0.0, -1.0);

    // Act
    const  math::Vector4D<float> ret = vec1.cross(vec2);

    // Assert
    for (int i = 0; i < 3; i++)
    {
        ASSERT_FLOAT_EQ(res[i], ret[i]);
    }
}

TEST(Vector4D, UnitZVectorWhenCrossWithUnitYVectorReturnsUnitNegativeVector)
{
    // Arrange
    const math::Vector4D<float> vec1(0.0, 0.0, 1.0);
    const math::Vector4D<float> vec2(0.0, 1.0, 0.0);

    const math::Vector4D<float> res(-1.0, 0.0, 0.0);

    // Act
    const math::Vector4D<float> ret = vec1.cross(vec2);

    // Assert
    for (int i = 0; i < 3; i++)
    {
        ASSERT_FLOAT_EQ(res[i], ret[i]);
    }
}

TEST(Vector4D, UnitVectorCrossWithItselfReturnZeroVector)
{
    // Arrange
    const math::Vector4D<float> vec(0.0, 0.0, 1.0);

    const math::Vector4D<float> res(0.0, 0.0, 0.0);

    // Act
    const math::Vector4D<float> ret = vec.cross(vec);

    // Assert
    for (int i = 0; i < 3; i++)
    {
        ASSERT_FLOAT_EQ(res[i], ret[i]);
    }
}

TEST(Vector4D, VectorCrossWithAnotherNonParallelVectorReturnsNewPerpendicularVector)
{
    // Arrange
    const math::Vector4D<float> vec1(2.0, 3.0, 4.0);
    const math::Vector4D<float> vec2(5.0, 6.0, 7.0);

    const math::Vector4D<float> res(-3.0, 6.0, -3.0);

    // Act
    const math::Vector4D<float> ret = vec1.cross(vec2);

    // Assert
    for (int i = 0; i < 3; i++)
    {
        ASSERT_FLOAT_EQ(res[i], ret[i]);
    }

    // Orientation Check: Dot must be zero
    const float dotProduct1 = vec1.dot(ret);
    const float dotProduct2 = vec2.dot(ret);

    ASSERT_FLOAT_EQ(0.0, dotProduct1);
    ASSERT_FLOAT_EQ(0.0, dotProduct2);
}

TEST(Vector4D, VectorCrossStaticWrapperWithAnotherNonParallelVectorReturnsNewPerpendicularVector)
{
    // Arrange
    const math::Vector4D<float> vec1(2.0, 3.0, 4.0);
    const math::Vector4D<float> vec2(5.0, 6.0, 7.0);

    math::Vector4D<float> res(-3.0, 6.0, -3.0);

    // Act
    math::Vector4D<float> ret = math::Vector4D<float>::cross(vec1, vec2);

    // Assert
    for (int i = 0; i < 3; i++)
    {
        ASSERT_FLOAT_EQ(res[i], ret[i]);
    }

    // Orientation Check: Dot must be zero
    const float dotProduct1 = math::Vector4D<float>::dot(vec1, ret);
    const float dotProduct2 = math::Vector4D<float>::dot(vec2, ret);

    ASSERT_FLOAT_EQ(0.0, dotProduct1);
    ASSERT_FLOAT_EQ(0.0, dotProduct2);
}