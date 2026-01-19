#include <gtest/gtest.h>

#include <Vector3D.h>

/*
* INITIALIZATION AND ACCESS TESTS
*/

TEST(Vector3D, EmptyConstructorInitializesUnitVector)
{
    math::Vector3D vec;

    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(1.0f, vec.z);
}

TEST(Vector3D, ConstructorParametersInitializesVector)
{
    math::Vector3D vec(3.0, 1.0, 6.0);

    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3D, AccessibleAsXYZ)
{
    math::Vector3D vec(3.0, 1.0, 6.0);

    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3D, AccessibleAsSTP)
{
    math::Vector3D vec(3.0, 1.0, 6.0);

    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
}

TEST(Vector3D, AccessibleAsRGB)
{
    math::Vector3D vec(3.0, 1.0, 6.0);

    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
}

TEST(Vector3D, AccessibleAsArray)
{
    math::Vector3D vec(3.0, 1.0, 6.0);

    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
}

TEST(Vector3D, VectorAddition) {
    math::Vector3D vec1(3.0f, 0.0f, -1.0f);
    math::Vector3D vec2(9.0f, -5.0f, 10.0f);

    math::Vector3D result = vec1 + vec2;

    EXPECT_FLOAT_EQ(12.0f, result.x);
    EXPECT_FLOAT_EQ(-5.0f, result.y);
    EXPECT_FLOAT_EQ(9.0f, result.z);
}