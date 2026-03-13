/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D<bool> bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

class BooleanVectorBitOperations: public ::testing::Test
{
    protected:
    fgm::Vector4D<bool> vecA;
    fgm::Vector4D<bool> vecB;
    fgm::Vector4D<bool> expectedAndVector;
    fgm::Vector4D<bool> expectedOrVector;
    fgm::Vector4D<bool> expectedNotAVector;

    void SetUp() override
    {
        vecA = { true, false, true, false };
        vecB = { true, true, false, false };
        expectedAndVector = { true, false, false, false };
        expectedOrVector = { true, true, true, false };
        expectedNotAVector = { false, true, false, true };
    }
};


/**************************************
 *                                    *
 *                TESTS               *
 *                                    *
 **************************************/

TEST_F(BooleanVectorBitOperations, BitwiseAndReturnsComponentwiseAnd)
{
    // Given two bool vectors

    // When they are `AND` together
    auto result = this->vecA & this->vecB;

    // Then, we get another vector with component-wise AND applied
    EXPECT_VEC_EQ(this->expectedAndVector, result);
}

TEST_F(BooleanVectorBitOperations, BitwiseOrReturnsComponentwiseOr)
{
    // Given two bool vectors

    // When they are `OR` together
    auto result = this->vecA | this->vecB;

    // Then, we get another vector with component-wise OR applied
    EXPECT_VEC_EQ(this->expectedOrVector, result);
}

TEST_F(BooleanVectorBitOperations, BitwiseNotReturnsInvertedVector)
{
    // Given a bool vector

    // When they are `OR` together
    auto result = !this->vecA;

    // Then, we get another vector with component-wise NOT applied
    EXPECT_VEC_EQ(this->expectedNotAVector, result);
}