/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"

using testutils::EXPECT_VEQ_CONTAINS;


/** @test Verify conversion constructor promotes type from float to double */
TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithPromotedType)
{
    const fgm::Vector4D vec1(3.0f, 1.0f, 6.0f, 2.0f);

    const fgm::Vector4D<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


/** @test Verify conversion constructor returns new instance */
TEST(Vector4DConversionConstructor, ReturnsNewInstance)
{   
    // Given a float vector
    fgm::Vector4D vec1(3.0f, 1.0f, 6.0f, 2.0f);

    // When converted to a double vector
    fgm::Vector4D<double> vec2(vec1);
    // And one of its value mutated
    vec2.x = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEQ_CONTAINS(vec1, 3.0f, 1.0f, 6.0f, 2.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEQ_CONTAINS(vec2, 5.0, 1.0, 6.0, 2.0);
}


/** @test Verify conversion constructor demotes type from double to float */
TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithDemotedType)
{
    const fgm::Vector4D vec1(3.0, 1.0, 6.0, 2.0);

    const fgm::Vector4D<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}
