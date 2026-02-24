#include <gtest/gtest.h>

#include <vector/Vector4D.h>

#include "../utils/VectorUtils.h"


using namespace TestUtils;

/****************
 *              *
 *  TEST SETUP  *
 *              *
 ****************/

// Turn off SIMD
#define FORCE_NO_SIMD // TODO: Update

using SupportedTypes = ::testing::Types<int, float, double, std::size_t>;

template<typename T>
class VectorInitializationTest: public ::testing::Test
{
protected:
};

TYPED_TEST_SUITE(VectorInitializationTest, SupportedTypes);



/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/


TEST(VectorInitializationTest, EmptyConstructorInitializesZeroVector)
{
    // Given a vector initialized without parameters
    const math::Vector4D<float> vec;

    // Then, it's elements form a zero vector
    EXPECT_VEC_ZERO(vec);
}

TYPED_TEST(VectorInitializationTest, ConstructorInitializesVectorsToCorrectValue)
{
	// Given 4 different values
    TypeParam a = static_cast<TypeParam>(3);
    TypeParam b = static_cast<TypeParam>(1);
    TypeParam c = static_cast<TypeParam>(6);
    TypeParam d = static_cast<TypeParam>(4);

    // When, a vector is initialized with those values
    const math::Vector4D<TypeParam> vec(a, b, c, d);

    // Then, the values are stored as elements of the vector
    if constexpr (std::is_same_v<TypeParam, float>)
    {
        EXPECT_FLOAT_EQ(a, vec.x);
        EXPECT_FLOAT_EQ(b, vec.y);
        EXPECT_FLOAT_EQ(c, vec.z);
        EXPECT_FLOAT_EQ(d, vec.w);
    }
    else if (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(a, vec.x);
        EXPECT_DOUBLE_EQ(b, vec.y);
        EXPECT_DOUBLE_EQ(c, vec.z);
        EXPECT_DOUBLE_EQ(d, vec.w);
    }
    else
    {
        EXPECT_EQ(a, vec.x);
        EXPECT_EQ(b, vec.y);
        EXPECT_EQ(c, vec.z);
        EXPECT_EQ(d, vec.w);
    }

}

TEST(Vector4DInitialization, Two2DVectorsCanInitializeA4DVector)
{
    // Given two 2D Vectors
    const math::Vector2D vec1(3.0f, 1.0f);
    const math::Vector2D vec2(6.0f, 2.0f);

    // When a Vector4D is initialized with those vectors
    const math::Vector4D vec(vec1, vec2);

    // Then, the 2D vector elements form the 4D vector
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}

TEST(Vector4DInitialization, One3DVectorAndScalarCanInitializeA4DVector)
{
    // Given a 3D Vector and a scalar
    const math::Vector3D vec1(3.0f, 1.0f, 6.0f);
    constexpr float scalar = 2.0f;

    // When a Vector4D is initialized with those vectors
    const math::Vector4D vec(vec1, scalar);

    // Then, the 3D vector elements + scalar form the 4D vector in the passed-in format
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(scalar, vec[3]);
}

TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithPromotedType)
{
    // Given a float vector
    math::Vector4D vec1(3.0f, 1.0f, 6.0f, 2.0f);

    // When it is converted to a double vector
    math::Vector4D<double> vec2(vec1);
    // And some values of new vector is mutated
	vec2.x = 5;

    // Then, the float vector remains unchanged
    ASSERT_FLOAT_EQ(3.0f, vec1.x);
    ASSERT_FLOAT_EQ(1.0f, vec1.y);
    ASSERT_FLOAT_EQ(6.0f, vec1.z);
    ASSERT_FLOAT_EQ(2.0f, vec1.w);

    // And, the new vector is of type double with the mutated value
    static_assert(std::is_same_v<typename decltype(vec2)::value_type, double>);
    ASSERT_DOUBLE_EQ(5.0, vec2.x);
    ASSERT_DOUBLE_EQ(1.0, vec2.y);
    ASSERT_DOUBLE_EQ(6.0, vec2.z);
    ASSERT_DOUBLE_EQ(2.0, vec2.w);

}

TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithDemotedType)
{
    // Given a double vector
    math::Vector4D vec1(3.0, 1.0, 6.0, 2.0);

    // When it is converted to a float vector
    math::Vector4D<float> vec2(vec1);
    // And some values of new vector is mutated
    vec2.x = 5;

    // Then, the float vector remains unchanged
    ASSERT_DOUBLE_EQ(3.0, vec1.x);
    ASSERT_DOUBLE_EQ(1.0, vec1.y);
    ASSERT_DOUBLE_EQ(6.0, vec1.z);
    ASSERT_DOUBLE_EQ(2.0, vec1.w);

    // And, the new vector is of type float with the mutated value
    static_assert(std::is_same_v<typename decltype(vec2)::value_type, float>);
    ASSERT_FLOAT_EQ(5.0f, vec2.x);
    ASSERT_FLOAT_EQ(1.0f, vec2.y);
    ASSERT_FLOAT_EQ(6.0f, vec2.z);
    ASSERT_FLOAT_EQ(2.0f, vec2.w);

}

TEST(Vector4DMutation, ElementsCanBeMutatedAtGivenIndex)
{
    // Given a vector initialization without parameters
    math::Vector4D<float> vec;

    // When it's elements are mutated at a particular index
    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    vec[3] = 2.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);

}

TEST(Vector4DAccess, AccessibleAsXYZ)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as x, y, z, w
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
    EXPECT_FLOAT_EQ(2.0f, vec.w);
}

TEST(Vector4DAccess, AccessibleAsSTP)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as s, t, p, q
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
    EXPECT_FLOAT_EQ(2.0f, vec.q);
}

TEST(Vector4DAccess, AccessibleAsRGB)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as r, g, b, a
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
    EXPECT_FLOAT_EQ(2.0f, vec.a);
}

TEST(Vector4DAccess, AccessibleAsArray)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as array elements
    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
    EXPECT_FLOAT_EQ(2.0f, vec.elements[3]);
}

TEST(Vector4DAccess, vec4Return3DFloatVector)
{
    // Given a vector is accessed as vec4
    constexpr bool isCorrectType = std::is_same_v<math::vec4::value_type, float>;

    // Then, it's value_type is float
    EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, dvec4Return3DDoubleVector)
{
    // Given a vector is accessed as dvec4
    constexpr bool isCorrectType = std::is_same_v<math::dvec4::value_type, double>;

    // Then, it's value_type is double
    EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, ivec4Return3DDoubleVector)
{
    // Given a vector is accessed as ivec4
    constexpr bool isCorrectType = std::is_same_v<math::ivec4::value_type, int>;

    // Then, it's value_type is integer
    EXPECT_TRUE(isCorrectType);
}


/*********************************
 *                               *
 *  SIMPLE MATH OPERATION TESTS  *
 *                               *
 *********************************/

TEST(Vector4DAddition, AdditionOperatorReturnsNewVectorWithSum)
{
    // Given vectors with arbitrary values
    const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f, 3.0f);
    const math::Vector4D expected(12.0f, -5.0f, 9.0f, 5.0f);

    // When they are added together
    const math::Vector4D result = vec1 + vec2;

    // Then the output vector contains sum of elements
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DAddition, AdditionAssignmentOperatorReturnsSameVectorWithSum)
{
    // Given vectors with arbitrary values
    math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0f, -5.0f, 10.0f, 3.0f);
    const math::Vector4D expected(12.0f, -5.0f, 9.0f, 5.0f);

    // When one vector is added to the other(+=)
   vec1 += vec2;

   // Then, the original matrix contains the sum of the elements added together
   EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector4DAddition, MixedTypeAdditionPromotesType)
{
    // Given vectors with arbitrary values
    const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
    const math::Vector4D expected(12.0, -5.0, 9.0, 5.0);

    // When they are added together
    const math::Vector4D result = vec1 + vec2;

    // Then the new vector is type promoted
    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
    // And contains sum of elements
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DAddition, MixedTypeAdditionAssignmentDoesNotPromoteType)
{
    // Given vectors with arbitrary values
    math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
    const math::Vector4D expected(12.0f, -5.0f, 9.0f, 5.0f);

    // When one vector is added to the other(+=)
    vec1 += vec2;

    // Then, the original vector's type is preserved
    static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
    // and contains sum of elements
    EXPECT_VEC_EQ(expected, vec1);
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

TEST(Vector4D, VectorTimesZeroIsZero)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 0;

    // Assert
    EXPECT_FLOAT_EQ(0.0f, newVec.x);
    EXPECT_FLOAT_EQ(0.0f, newVec.y);
    EXPECT_FLOAT_EQ(0.0f, newVec.z);
    EXPECT_FLOAT_EQ(0.0f, newVec.w);
}

TEST(Vector4D, VectorTimesOneIsItself)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 1;

    // Assert
    EXPECT_FLOAT_EQ(3.0f, newVec.x);
    EXPECT_FLOAT_EQ(1.0f, newVec.y);
    EXPECT_FLOAT_EQ(6.0f, newVec.z);
    EXPECT_FLOAT_EQ(2.0f, newVec.w);
}

TEST(Vector4D, VectorTimesANumberIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 2;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, newVec.x);
    EXPECT_FLOAT_EQ(2.0f, newVec.y);
    EXPECT_FLOAT_EQ(12.0f, newVec.z);
    EXPECT_FLOAT_EQ(4.0f, newVec.w);
}

TEST(Vector4D, VectorTimesAFloatIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec * 2.0;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, newVec.x);
    EXPECT_FLOAT_EQ(2.0f, newVec.y);
    EXPECT_FLOAT_EQ(12.0f, newVec.z);
    EXPECT_FLOAT_EQ(4.0f, newVec.w);
}

TEST(Vector4D, NumberTimesAVectorIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = 2 * vec;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, newVec.x);
    EXPECT_FLOAT_EQ(2.0f, newVec.y);
    EXPECT_FLOAT_EQ(12.0f, newVec.z);
    EXPECT_FLOAT_EQ(4.0f, newVec.w);
}

TEST(Vector4D, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec *= 2;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
    EXPECT_FLOAT_EQ(12.0f, vec.z);
    EXPECT_FLOAT_EQ(4.0f, vec.w);
}

TEST(Vector4D, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec *= 2.0;

    // Assert
    EXPECT_FLOAT_EQ(6.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
    EXPECT_FLOAT_EQ(12.0f, vec.z);
    EXPECT_FLOAT_EQ(4.0f, vec.w);
}


TEST(Vector4D, VectorDividedByZeroIsInfinity)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 0;

    // Assert
    EXPECT_FLOAT_EQ(INFINITY, newVec.x);
    EXPECT_FLOAT_EQ(INFINITY, newVec.y);
    EXPECT_FLOAT_EQ(INFINITY, newVec.z);
    EXPECT_FLOAT_EQ(INFINITY, newVec.w);
}

TEST(Vector4D, VectorDividedByOneIsItself)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 1;

    // Assert
    EXPECT_FLOAT_EQ(3.0f, newVec.x);
    EXPECT_FLOAT_EQ(1.0f, newVec.y);
    EXPECT_FLOAT_EQ(6.0f, newVec.z);
    EXPECT_FLOAT_EQ(2.0f, newVec.w);
}

TEST(Vector4D, VectorDividedByANumberIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 2;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, newVec.x);
    EXPECT_FLOAT_EQ(0.5f, newVec.y);
    EXPECT_FLOAT_EQ(3.0f, newVec.z);
    EXPECT_FLOAT_EQ(1.0f, newVec.w);
}

TEST(Vector4D, VectorDividedByAFloatIsANewVector)
{
    // Arrange
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    const math::Vector4D newVec = vec / 2.0;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, newVec.x);
    EXPECT_FLOAT_EQ(0.5f, newVec.y);
    EXPECT_FLOAT_EQ(3.0f, newVec.z);
    EXPECT_FLOAT_EQ(1.0f, newVec.w);
}

TEST(Vector4D, VectorDividesEqualAScalarIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec /= 2;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, vec.x);
    EXPECT_FLOAT_EQ(0.5f, vec.y);
    EXPECT_FLOAT_EQ(3.0f, vec.z);
    EXPECT_FLOAT_EQ(1.0f, vec.w);
}

TEST(Vector4D, VectorDividesEqualAFloatIsSameVectorWithNewValues)
{
    // Arrange
    math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Act
    vec /= 2.0;

    // Assert
    EXPECT_FLOAT_EQ(1.5f, vec.x);
    EXPECT_FLOAT_EQ(0.5f, vec.y);
    EXPECT_FLOAT_EQ(3.0f, vec.z);
    EXPECT_FLOAT_EQ(1.0f, vec.w);
}

/***************************************
 *                                     *
 *  MAGNITUDE AND NORMALIZATION TESTS  *
 *                                     *
 ***************************************/

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

TEST(Vector4D, VectorWhenNormalizedReturnsANormalVector)
{
    // Arrange
    const math::Vector4D vec(1.0f, 2.0f, 2.0f, 4.0f);

    // Act
    const math::Vector4D normalized = vec.normalize();

    // Assert
    EXPECT_FLOAT_EQ(0.2f, normalized.x);
    EXPECT_FLOAT_EQ(0.4f, normalized.y);
    EXPECT_FLOAT_EQ(0.4f, normalized.z);
    EXPECT_FLOAT_EQ(0.8f, normalized.w);
}


/***********************
 *                     *
 *  DOT PRODUCT TESTS  *
 *                     *
 ***********************/

TEST(Vector4D, VectorWhenDotWithItselfReturnsOne)
{
	// Arrange
    const math::Vector4D<float> vec(1.0, 0.0, 0.0, 0.0);

    // Act
    const float res = vec.dot(vec);

    // Assert
    EXPECT_FLOAT_EQ(1.0, res);
}

TEST(Vector4D, VectorWhenDotWithOrthogonalVectorReturnZero)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 0.0, 0.0, 0.0);
    const math::Vector4D<float> vec2(0.0, 1.0, 0.0, 0.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    EXPECT_FLOAT_EQ(0.0, res);
}

TEST(Vector4D, VectorWhenDotWithOppositeParallelVectorReturnsNegativeOne)
{
    // Arrange
    const math::Vector4D<float> vec1(1.0, 0.0, 0.0, 0.0);
    const math::Vector4D<float> vec2(-1.0, 0.0, 0.0, 0.0);

    // Act
    const float res = vec1.dot(vec2);

    // Assert
    EXPECT_FLOAT_EQ(-1.0, res);
}


/************************************
 *                                  *
 *  PROJECTION AND REJECTION TESTS  *
 *                                  *
 ************************************/

TEST(Vector4D, ParallelVectorsWhenProjectedReturnsNonZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 5.0f);
    const math::Vector4D b(2.0f, 4.0f, 6.0f, 10.0f);
    const math::Vector4D expectedProjection(1.0f, 2.0f, 3.0f, 5.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.project(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorWhenProjectedOntoXAxisProducesVectorWithOnlyXComponent)
{
    // Arrange
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.f);
    const math::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const math::Vector4D expectedProjection(10.0f, 0.0f, 0.0f, 0.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.project(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorWhenProjectedOntoWAxisProducesVectorWithOnlyWComponent)
{
    // Arrange
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.f);
    const math::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);
    const math::Vector4D expectedProjection(0.0f, 0.0f, 0.0f, 40.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.project(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorsWhenProjectedReturnsNonZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 0.0f, 1.0f);
    const math::Vector4D b(2.0f, 0.0f, 1.0f, 1.0f);
    const math::Vector4D expectedProjection(1.0f, 0.0f, 0.5f, 0.5f);

    // Act
    const math::Vector4D<float> actualProjection = a.project(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorsWhenProjectedOntoNormalizedVectorReturnsNonZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const math::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const math::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.project(b, true);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorsWhenProjectedOntoNegativeVectorReturnsNonZeroVectorInSameDirection)
{
    // Arrange
    const math::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const math::Vector4D b(0.0f, 0.0f, -1.0f, 0.0f);
    const math::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.project(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorsWhenProjectedUsingStaticWrapperReturnsNonZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 0.0f, 1.0f);
    const math::Vector4D b(2.0f, 0.0f, 1.0f, 1.0f);
    const math::Vector4D expectedProjection(1.0f, 0.0f, 0.5f, 0.5f);

    // Act
    const math::Vector4D<float> actualProjection = math::Vector4D<float>::project(a, b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}


TEST(Vector4D, ParallelVectorsWhenRejectedReturnsZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 5.0f);
    const math::Vector4D b(2.0f, 4.0f, 6.0f, 10.0f);
    const math::Vector4D expectedProjection(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.reject(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, PerpendicularVectorsWhenRejectedWReturnsNonZeroVectorWithZeroWComponent)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const math::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);
    const math::Vector4D expectedProjection(1.0f, 2.0f, 3.0f, 0.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.reject(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, RejectingNonExistantComponentReturnsSameVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    const math::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.reject(b);

    // Assert
    EXPECT_FLOAT_EQ(a.x, actualProjection.x);
    EXPECT_FLOAT_EQ(a.y, actualProjection.y);
    EXPECT_FLOAT_EQ(a.z, actualProjection.z);
    EXPECT_FLOAT_EQ(a.w, actualProjection.w);
}

TEST(Vector4D, VectorsWhenRejectedReturnNonZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 0.0f, 1.0f);
    const math::Vector4D b(2.0f, 0.0f, 1.0f, 1.0f);
    const math::Vector4D expectedProjection(0.0f, 2.0f, -0.5f, 0.5f);

    // Act
    const math::Vector4D<float> actualProjection = a.reject(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorsWhenRejectedOntoNormalizedVectorReturnNonZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const math::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const math::Vector4D expectedProjection(0.0f, 2.0f, 3.0f, 4.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.reject(b, true);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, PositiveVectorsWhenRejectedOntoNegativeVectorReturnsNonZeroVectorNonZeroPositiveVector)
{
    // Arrange
    const math::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const math::Vector4D b(0.0f, 0.0f, -1.0f, 0.0f);
    const math::Vector4D expectedProjection(4.0f, 4.0f, 0.0f, 4.0f);

    // Act
    const math::Vector4D<float> actualProjection = a.reject(b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4D, VectorsWhenProjectedUsingStaticWrapperReturnNonZeroVector)
{
    // Arrange
    const math::Vector4D a(1.0f, 2.0f, 0.0f, 1.0f);
    const math::Vector4D b(2.0f, 0.0f, 1.0f, 1.0f);
    const math::Vector4D expectedProjection(0.0f, 2.0f, -0.5f, 0.5f);

    // Act
    const math::Vector4D<float> actualProjection = math::Vector4D<float>::reject(a, b);

    // Assert
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}