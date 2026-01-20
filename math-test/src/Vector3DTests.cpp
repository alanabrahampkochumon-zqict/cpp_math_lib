#include <gtest/gtest.h>

#include <Vector3D.h>

/*
* INITIALIZATION AND ACCESS TESTS
*/

TEST(Vector3D, EmptyConstructorInitializesUnitVector)
{
    // Arrange & Act
    math::Vector3D vec;

    // Assert
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(1.0f, vec.z);
}

TEST(Vector3D, ConstructorParametersInitializesVector)
{
    // Arrange & Act
    math::Vector3D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3D, AccessibleAsXYZ)
{
    // Arrange & Act
    math::Vector3D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3D, AccessibleAsSTP)
{
    // Arrange & Act
    math::Vector3D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
}

TEST(Vector3D, AccessibleAsRGB)
{
    // Arrange & Act
    math::Vector3D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
}

TEST(Vector3D, AccessibleAsArray)
{
    // Arrange & Act
    math::Vector3D vec(3.0, 1.0, 6.0);

    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
}

TEST(Vector3D, IndexBasedAssignmentAndRetrivalSupport)
{
    // Arrange
    math::Vector3D vec;

    // Act
    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    
    // Assert
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);

}

/*
    VECTOR OPERATIONS TESTS
*/

TEST(Vector3D, VectorAddition)
{
    // Arrange
    math::Vector3D vec1(3.0f, 0.0f, -1.0f);
    math::Vector3D vec2(9.0f, -5.0f, 10.0f);

    // Act
    math::Vector3D result = vec1 + vec2;

    // Assert
    EXPECT_FLOAT_EQ(12.0f, result.x);
    EXPECT_FLOAT_EQ(-5.0f, result.y);
    EXPECT_FLOAT_EQ(9.0f, result.z);
}

TEST(Vector3D, VectorSubtraction)
{
    // Arrange
    math::Vector3D vec1(3.0f, 0.0f, -1.0f);
    math::Vector3D vec2(9.0f, -5.0f, 10.0f);

    // Act
    math::Vector3D result = vec1 - vec2;

    // Assert
    EXPECT_FLOAT_EQ(-6.0f, result.x);
    EXPECT_FLOAT_EQ(5.0f, result.y);
    EXPECT_FLOAT_EQ(-11.0f, result.z);
}

TEST(Vector3D, ZeroVectorReturnsMagnitudeZero)
{
    // Arrange
    math::Vector3D vec(0.0f, 0.0f, 0.0f);

    // Act
    float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector3D, UnitVectorReturnsMagnitudeNotEqualToOne)
{
    // Arrange
    math::Vector3D vec;

    // Act
    float magnitude = vec.mag();

    // Assert
    EXPECT_GT(1.5f, magnitude);
    EXPECT_LT(2.0f, magnitude);
}

TEST(Vector3D, NonUnitVectorReturnsCorrectMagnitude)
{
    // Arrange
    math::Vector3D vec(2.0f, 3.0f, 6.0f);

    // Act
    float magnitude = vec.mag();

    // Assert
    EXPECT_FLOAT_EQ(7.0f, magnitude);
}