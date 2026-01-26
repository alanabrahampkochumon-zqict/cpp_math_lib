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
    EXPECT_FLOAT_EQ(0.0f, vec.w);
}

TEST(Vector4D, ConstructorParametersInitializesVector)
{
    // Arrange & Act
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
    EXPECT_FLOAT_EQ(2.0f, vec.w);
}

TEST(Vector4D, AccessibleAsXYZ)
{
    // Arrange & Act
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
    EXPECT_FLOAT_EQ(2.0f, vec.w);
}

TEST(Vector4D, AccessibleAsSTP)
{
    // Arrange & Act
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
    EXPECT_FLOAT_EQ(2.0f, vec.q);
}

TEST(Vector4D, AccessibleAsRGB)
{
    // Arrange & Act
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
    EXPECT_FLOAT_EQ(2.0f, vec.a);
}

TEST(Vector4D, AccessibleAsArray)
{
    // Arrange & Act
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
    EXPECT_FLOAT_EQ(2.0f, vec.elements[3]);
}

TEST(Vector4D, IndexBasedAssignmentAndRetrivalSupport)
{
    // Arrange
    math::Vector4D<float> vec;

    // Act
    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    vec[3] = 2.0f;
    
    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);

}

TEST(Vector4D, vec4Return3DFloatVector)
{
    // Arrange & Act
    constexpr bool isCorrectType = std::is_same_v<math::vec4, math::Vector4D<float>>;

    // Assert
    EXPECT_TRUE(isCorrectType);
}

TEST(Vector4D, dvec4Return3DDoubleVector)
{
    // Arrange & Act
    constexpr bool isCorrectType = std::is_same_v<math::dvec4, math::Vector4D<double>>;

    // Assert
    EXPECT_TRUE(isCorrectType);
}

TEST(Vector4D, two2DVectorsCanInitializeA4DVector)
{
    // Arrange
    math::Vector2D vec1(3.0f, 1.0f);
    math::Vector2D vec2(6.0f, 2.0f);

    // Act
    math::Vector4D vec(vec1, vec2);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}

TEST(Vector4D, one3DVectorAndFloatCanInitializeA4DVector)
{
    // Arrange
    math::Vector3D vec1(3.0f, 1.0f, 6.0f);

    // Act
    math::Vector4D vec(vec1, 2.0f);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}

/*
*   VECTOR OPERATIONS TESTS
*/

TEST(Vector4D, VectorAddition)
{
    // Arrange
    const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f, 3.0f);

    // Act
    const math::Vector4D result = vec1 + vec2;

    // Assert
    EXPECT_FLOAT_EQ(12.0f, result.x);
    EXPECT_FLOAT_EQ(-5.0f, result.y);
    EXPECT_FLOAT_EQ(9.0f, result.z);
    EXPECT_FLOAT_EQ(5.0f, result.w);
}

TEST(Vector4D, VectorPlusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
    // Arrange
    math::Vector4D vec1(3.0f, 0.0f, -1.0f, 8.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f, 5.0f);

    // Act
   vec1 += vec2;

    // Assert
    EXPECT_FLOAT_EQ(12.0f, vec1.x);
    EXPECT_FLOAT_EQ(-5.0f, vec1.y);
    EXPECT_FLOAT_EQ(9.0f, vec1.z);
    EXPECT_FLOAT_EQ(13.0f, vec1.w);
}

TEST(Vector4D, VectorSubtraction)
{
    // Arrange
    math::Vector4D vec1(3.0f, 0.0f, -1.0f, 8.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f, 5.0f);

    // Act
    const math::Vector4D result = vec1 - vec2;

    // Assert
    EXPECT_FLOAT_EQ(-6.0f, result.x);
    EXPECT_FLOAT_EQ(5.0f, result.y);
    EXPECT_FLOAT_EQ(-11.0f, result.z);
    EXPECT_FLOAT_EQ(3.0f, result.w);
}

TEST(Vector4D, VectorMinusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
    // Arrange
    math::Vector4D vec1(3.0f, 0.0f, -1.0f, 8.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f, 5.0f);

    // Act
    vec1 -= vec2;

    // Assert
    EXPECT_FLOAT_EQ(-6.0f, vec1.x);
    EXPECT_FLOAT_EQ(5.0f, vec1.y);
    EXPECT_FLOAT_EQ(-11.0f, vec1.z);
    EXPECT_FLOAT_EQ(3.0f, vec1.w);
}

TEST(Vector4D, ZeroVectorReturnsMagnitudeZero)
{
    // Arrange
    const math::Vector4D vec(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector4D, OneVectorReturnsMagnitudeNotEqualToOne)
{
    // Arrange
    const math::Vector4D vec(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_NE(1.0f, magnitude);
}

TEST(Vector4D, NonUnitVectorReturnsCorrectMagnitude)
{
    // Arrange
    const math::Vector4D vec(1.0f, 2.0f, 2.0f, 4.0f);

    // Act
    const float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(5.0f, magnitude);
}

TEST(Vector4D, VectorTimesZeroIsZero)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 0;

    // Assert
    ASSERT_FLOAT_EQ(0.0f, newVec.x);
    ASSERT_FLOAT_EQ(0.0f, newVec.y);
    ASSERT_FLOAT_EQ(0.0f, newVec.z);
    ASSERT_FLOAT_EQ(0.0f, newVec.w);
}

TEST(Vector4D, VectorTimesOneIsItself)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 1;

    // Assert
    ASSERT_FLOAT_EQ(3.0f, newVec.x);
    ASSERT_FLOAT_EQ(1.0f, newVec.y);
    ASSERT_FLOAT_EQ(6.0f, newVec.z);
    ASSERT_FLOAT_EQ(2.0f, newVec.w);
}

TEST(Vector4D, VectorTimesANumberIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 2;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
    ASSERT_FLOAT_EQ(12.0f, newVec.z);
    ASSERT_FLOAT_EQ(4.0f, newVec.w);
}

TEST(Vector4D, VectorTimesAFloatIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 2.0;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
    ASSERT_FLOAT_EQ(12.0f, newVec.z);
    ASSERT_FLOAT_EQ(4.0f, newVec.w);
}

TEST(Vector4D, NumberTimesAVectorIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = 2 * vec;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, newVec.x);
    ASSERT_FLOAT_EQ(2.0f, newVec.y);
    ASSERT_FLOAT_EQ(12.0f, newVec.z);
    ASSERT_FLOAT_EQ(4.0f, newVec.w);
}

TEST(Vector4D, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec *= 2;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, vec.x);
    ASSERT_FLOAT_EQ(2.0f, vec.y);
    ASSERT_FLOAT_EQ(12.0f, vec.z);
    ASSERT_FLOAT_EQ(4.0f, vec.w);
}

TEST(Vector4D, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec *= 2.0;

    // Assert
    ASSERT_FLOAT_EQ(6.0f, vec.x);
    ASSERT_FLOAT_EQ(2.0f, vec.y);
    ASSERT_FLOAT_EQ(12.0f, vec.z);
    ASSERT_FLOAT_EQ(4.0f, vec.w);
}


TEST(Vector4D, VectorDividedByZeroIsInfinity)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 0;

    // Assert
    ASSERT_FLOAT_EQ(INFINITY, newVec.x);
    ASSERT_FLOAT_EQ(INFINITY, newVec.y);
    ASSERT_FLOAT_EQ(INFINITY, newVec.z);
    ASSERT_FLOAT_EQ(INFINITY, newVec.w);
}

TEST(Vector4D, VectorDividedByOneIsItself)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 1;

    // Assert
    ASSERT_FLOAT_EQ(3.0f, newVec.x);
    ASSERT_FLOAT_EQ(1.0f, newVec.y);
    ASSERT_FLOAT_EQ(6.0f, newVec.z);
    ASSERT_FLOAT_EQ(2.0f, newVec.w);
}

TEST(Vector4D, VectorDividedByANumberIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 2;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, newVec.x);
    ASSERT_FLOAT_EQ(0.5f, newVec.y);
    ASSERT_FLOAT_EQ(3.0f, newVec.z);
    ASSERT_FLOAT_EQ(1.0f, newVec.w);
}

TEST(Vector4D, VectorDividedByAFloatIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 2.0;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, newVec.x);
    ASSERT_FLOAT_EQ(0.5f, newVec.y);
    ASSERT_FLOAT_EQ(3.0f, newVec.z);
    ASSERT_FLOAT_EQ(1.0f, newVec.w);
}

TEST(Vector4D, VectorDividesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec /= 2;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, vec.x);
    ASSERT_FLOAT_EQ(0.5f, vec.y);
    ASSERT_FLOAT_EQ(3.0f, vec.z);
    ASSERT_FLOAT_EQ(1.0f, vec.w);
}

TEST(Vector4D, VectorDividesEqualAFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec /= 2.0;

    // Assert
    ASSERT_FLOAT_EQ(1.5f, vec.x);
    ASSERT_FLOAT_EQ(0.5f, vec.y);
    ASSERT_FLOAT_EQ(3.0f, vec.z);
    ASSERT_FLOAT_EQ(1.0f, vec.w);
}


TEST(Vector4D, VectorWhenNormalizedReturnsANormalVector)
{
    // Arrange
    const math::Vector4D vec(1.0f, 2.0f, 2.0f, 4.0f);

    // Act
    const math::Vector4D normalized = vec.normalize();

    // Assert
    ASSERT_FLOAT_EQ(0.2f, normalized.x);
    ASSERT_FLOAT_EQ(0.4f, normalized.y);
    ASSERT_FLOAT_EQ(0.4f, normalized.z);
    ASSERT_FLOAT_EQ(0.8f, normalized.w);
}

// Dot Product
TEST(Vector4D, VectorWhenDotWithItselfReturnsOne)
{
	// Arrange
    const math::Vector4D<float> vec(1.0, 0.0, 0.0, 0.0);

    // Act
    const float res = vec.dot(vec);

    // Assert
    ASSERT_FLOAT_EQ(1.0, res);
}

TEST(Vector4D, VectorWhenDotWithOrthogonalVectorReturnZero)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 0.0, 0.0, 0.0);
    const math::Vector4D<float> vec2(0.0, 1.0, 0.0, 0.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(0.0, res);
}

TEST(Vector4D, VectorWhenDotWithOppositeParallelVectorReturnsNegativeOne)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 0.0, 0.0, 0.0);
    const math::Vector4D<float> vec2(-1.0, 0.0, 0.0, 0.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    ASSERT_FLOAT_EQ(-1.0, res);
}
