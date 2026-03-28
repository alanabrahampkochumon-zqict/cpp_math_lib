/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector4DMagnitude: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec = { T(1), T(2), T(2), T(4) };
        _expectedMagnitude = fgm::Magnitude<T>(5);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D magnitude, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DMagnitude, SupportedArithmeticTypes);


template <typename T>
class Vector4DUncleanMagnitude: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec = { T(1), T(2), T(3), T(4) };
        _expectedMagnitude = fgm::Magnitude<T>(5.477225575051661);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D magnitude, parameterized by SupportedArithmeticTypes, for testing
 * high-precision magnitude. */
TYPED_TEST_SUITE(Vector4DUncleanMagnitude, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Magnitude
 * @{
 */

/** @test Verify that the magnitude of a zero @ref fgm::Vector4D returns exactly zero. */
TEST(Vector4DMagnitude, ZeroVectorReturnsZero)
{
    constexpr fgm::Vector4D vec(0.0f, 0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}

/** @test Verify that the magnitude of a @ref fgm::Vector4D with multiple unit-component returns non-unit magnitude. */
TEST(Vector4DMagnitude, OneComponentVectorReturnsNonUnitScalar)
{
    constexpr fgm::Vector4D vec(1.0f, 1.0f, 1.0f, 1.0f);

    EXPECT_NE(1.0f, vec.mag());
}

/** @test Verify that the magnitude of a non-unit @ref fgm::Vector4D returns a non-unit magnitude. */
TYPED_TEST(Vector4DMagnitude, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}

/**
 * @test Verify that the @ref fgm::Vector4D magnitude calculation results in a floating-point type, regardless of the
 *       component type.
 */
TYPED_TEST(Vector4DMagnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}

/** @test Verify that the static magnitude wrapper of @ref fgm::Vector4D returns a non-unit magnitude. */
TYPED_TEST(Vector4DMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Vector4D<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}

/**
 * @test Verify the numerical accuracy of @ref fgm::Vector4D magnitude calculations for non-unit vectors to ensure
 *        minimal precision loss.
 */
TYPED_TEST(Vector4DUncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}

/**
 * @test Verify the numerical accuracy of @ref fgm::Vector4D static magnitude wrapper for non-unit vectors ensure
 *        minimal precision loss.
 */
TYPED_TEST(Vector4DUncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = fgm::Vector4D<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}

/** @} */