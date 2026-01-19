#include <gtest/gtest.h>

#include <Vector3D.h>

TEST(Vector3D, EmptyConstructorInitializesUnitVector)
{
    math::Vector3D vec;

    EXPECT_FLOAT_EQ(1.0f, vec.v1);
    EXPECT_FLOAT_EQ(1.0f, vec.v2);
    EXPECT_FLOAT_EQ(1.0f, vec.v3);
}