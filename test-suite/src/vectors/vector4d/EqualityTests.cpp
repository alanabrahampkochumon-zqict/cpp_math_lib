/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * allNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


template <typename T>
class Vector4DEquality: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> eqVecA;
    fgm::Vector4D<T> eqVecB;
    fgm::Vector4D<T> dissimilarVec;
    fgm::Vector4D<bool> equalityMask;
    fgm::Vector4D<bool> inequalityMask;


    void SetUp() override
    {
        eqVecA = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        eqVecB = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        dissimilarVec = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
        equalityMask = { false, true, false, true };
        inequalityMask = { true, false, true, false };
    }
};
/** @brief Typed test suite for Vector Equality and Inequality checks. */
TYPED_TEST_SUITE(Vector4DEquality, SupportedArithmeticTypes);





/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/


/** @test Verify @ref fgm::Vector4D::allEq return true for identical vectors. */
TYPED_TEST(Vector4DEquality, IdenticalVectorsAreEqual)
{
    bool equality = this->eqVecA.allEq(this->eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq return false if any component differ. */
TYPED_TEST(Vector4DEquality, DissimilarVectorsAreNotEqual)
{
    bool equality = this->eqVecA.allEq(this->dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify static variant of @ref fgm::Vector4D::allEq for identical vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_IdenticalVectorsAreEqual)
{
    bool equality = fgm::Vector4D<TypeParam>::allEq(this->eqVecA, this->eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify static variant of @ref fgm::Vector4D::allEq for different vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_DissimilarVectorsAreNotEqual)
{
    bool equality = fgm::Vector4D<TypeParam>::allEq(this->eqVecA, this->dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanEqualityReturnsFalse)
{
    fgm::Vector4D vecA = { NAN, NAN, NAN, NAN };
    fgm::Vector4D<double> vecB = { 1.0, -5.88874789, INFINITY, NAN };

    bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    fgm::Vector4D vecA = { INFINITY, -INFINITY, INFINITY, -INFINITY };
    fgm::Vector4D vecB = { INFINITY, -INFINITY, INFINITY, -INFINITY };

    bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    fgm::Vector4D vecA = { INFINITY, INFINITY, INFINITY, -INFINITY };
    fgm::Vector4D vecB = { INFINITY, -INFINITY, INFINITY, INFINITY };

    bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator returns true for identical vectors. */
TYPED_TEST(Vector4DEquality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    bool equality = this->eqVecA == this->eqVecB;

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator returns false if any component differ. */
TYPED_TEST(Vector4DEquality, EqualityOperator_DissimilarVectorsReturnsFalse)
{
    bool equality = this->eqVecA == this->dissimilarVec;

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for different vector types with identical components. */
TYPED_TEST(Vector4DEquality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(1, 2, 3, 4);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for different vector types with different components. */
TYPED_TEST(Vector4DEquality, MixedType_Equality_DissimilarVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(5, 6, 7, 8);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for bool vector with identical components. */
TEST(Vector4DEquality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, false, true, false);

    bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for bool vector with different components. */
TEST(Vector4DEquality, EqualityOperator_DissimilarBooleanVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, true, true, false);

    bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D::eq return @ref fgm::Vector4D<bool> mask for identical vectors. */
TYPED_TEST(Vector4DEquality, EqualityMaskReturnsCorrectBooleanMask)
{
    fgm::Vector4D<bool> mask = this->eqVecA.eq(this->dissimilarVec);

    EXPECT_VEC_EQ(this->equalityMask, mask);
}


/** @test Verify @ref fgm::Vector4D::eq return @ref fgm::Vector4D<bool> mask for different vectors. */
TEST(Vector4DEquality, MixedType_EqualityMaskReturnsCorrectBooleanMask)
{
    fgm::Vector4D vecA = { 1, 2, 3, 4 };
    fgm::Vector4D vecB = { 1.0, 4.0, 0.0, 4.0 };
    fgm::Vector4D expectedMask = { true, false, false, true };

    fgm::Vector4D<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify @ref fgm::Vector4D::eq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanEqualityReturnsFalseBooleanMask)
{
    // When a vector with only NAN is compared with another vector
    fgm::Vector4D vecA = { NAN, NAN, NAN, NAN };
    fgm::Vector4D<double> vecB = { 1.0, -5.88874789, INFINITY, NAN };
    fgm::Vector4D expectedMask = { false, false, false, false };

    fgm::Vector4D mask = vecA.eq(vecB);

    // Then, boolean masks contains only false values
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify @ref fgm::Vector4D::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEqualityReturnsCorrectBooleanMask)
{
    // When an infinity vector is compared with another
    fgm::Vector4D vecA = { INFINITY, -INFINITY, INFINITY, -INFINITY };
    fgm::Vector4D<double> vecB = { INFINITY, INFINITY, 10e11, 10e11 };
    fgm::Vector4D expectedMask = { true, false, false, false };

    fgm::Vector4D mask = vecA.eq(vecB);

    // Then, boolean masks contains correct values
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify static variant of @ref fgm::Vector4D::eq return @ref fgm::Vector4D<bool> mask for different vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_EqualityMaskReturnsCorrectBooleanMask)
{
    // When two vectors are compared for component-wise equality
    fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::eq(this->eqVecA, this->dissimilarVec);

    // Then, correct boolean mask is returned
    EXPECT_VEC_EQ(this->equalityMask, mask);
}




/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/


/** @test Verify @ref fgm::Vector4D inequality operator return false for identical vectors. */
TYPED_TEST(Vector4DEquality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    bool equality = this->eqVecA != this->eqVecB;

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D inequality operator return true for different vectors. */
TYPED_TEST(Vector4DEquality, InEqualityOperator_DissimilarVectorsReturnsTrue)
{
    bool equality = this->eqVecA != this->dissimilarVec;

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for different vector types with identical components. */
TYPED_TEST(Vector4DEquality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(1, 2, 3, 4);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for different vector types with different components. */
TYPED_TEST(Vector4DEquality, MixedType_Inequality_DissimilarVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(5, 6, 7, 8);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for @ref fgm::Vector4D<bool> with identical components. */
TEST(Vector4DEquality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, false, true, false);

    bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator works for @ref fgm::Vector4D<bool> with different components. */
TEST(Vector4DEquality, InequalityOperator_DissimilarBooleanVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, true, true, false);

    bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}
