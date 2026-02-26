#include <gtest/gtest.h>

#include <vector/Vector4D.h>
#include <MathTraits.h>

#include "../utils/VectorUtils.h"


using namespace TestUtils;

/****************
 *              *
 *  TEST SETUP  *
 *              *
 ****************/

 // Turn off SIMD
#define FORCE_NO_SIMD // TODO: Update

using SupportedTypes = ::testing::Types<unsigned char, int, unsigned int, float, double, std::size_t, long long>;


/**************************
 *                        *
 *  INITIALIZATION SETUP  *
 *                        *
 **************************/

template<typename T>
class VectorInitialization : public ::testing::Test { };
TYPED_TEST_SUITE(VectorInitialization, SupportedTypes);


/*********************************
 *                               *
 *  ARITHMETIC OPERATIONS SETUP  *
 *                               *
 *********************************/

template <typename T>
class Vector4DAddition : public ::testing::Test
{
protected:
	math::Vector4D<T> vecA;
	math::Vector4D<T> vecB;
	math::Vector4D<T> expected;

	void SetUp() override
	{
		vecA = { T(3), T(1), T(6), T(2) };
		vecB = { T(-8) , T(5), T(-2), T(5) };
		expected = { T(-5) , T(6), T(4), T(7) };
	}
};
TYPED_TEST_SUITE(Vector4DAddition, SupportedTypes);


template <typename T>
class Vector4DSubtraction : public ::testing::Test
{
protected:
	math::Vector4D<T> vecA;
	math::Vector4D<T> vecB;
	math::Vector4D<T> expected;

	void SetUp() override
	{
		vecA = { T(95), T(11), T(-6), T(2) };
		vecB = { T(-8) , T(5), T(-2), T(-5) };
		expected = { T(103) , T(6), T(-4), T(7) };
	}
};
TYPED_TEST_SUITE(Vector4DSubtraction, SupportedTypes);


template <typename T>
class Vector4DScalarMultiplication : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	T scalar;
	math::Vector4D<T> expected;

	void SetUp() override
	{
		vec = { T(5), T(9), T(-8), T(-2) };
		scalar = T(5);
		expected = { T(25), T(45), T(-40), T(-10) };
	}
};
TYPED_TEST_SUITE(Vector4DScalarMultiplication, SupportedTypes);


template<typename T>
class Vector4DScalarDivision : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	T scalar;
	math::Vector4D<T> expected;

	void SetUp() override
	{
		vec = { T(5), T(35), T(40), T(100) };
		scalar = T(5);
		expected = { T(1), T(7), T(8), T(20) };
	}

};
TYPED_TEST_SUITE(Vector4DScalarDivision, SupportedTypes);


/***************************************
 *                                     *
 *  MAGNITUDE AND NORMALIZATION SETUP  *
 *                                     *
 ***************************************/

template <typename T>
class Vector4DMagnitude: public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	math::Magnitude<T> magnitude;

	void SetUp() override
	{
		vec = { T(1), T(2), T(2), T(4) };
		magnitude = math::Magnitude<T>(5);
	}
};
TYPED_TEST_SUITE(Vector4DMagnitude, SupportedTypes);


template <typename T>
class Vector4DUncleanMagnitude : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	math::Magnitude<T> magnitude;

	void SetUp() override
	{
		vec = { T(1), T(2), T(3), T(4) };
		magnitude = math::Magnitude<T>(5.477225575051661);
	}
};
TYPED_TEST_SUITE(Vector4DUncleanMagnitude, SupportedTypes);


template <typename T>
class Vector4DNormalization : public ::testing::Test
{
	using R = math::Magnitude<T>;
protected:
	math::Vector4D<T> vec;
	math::Vector4D<R> expectedVector;

	void SetUp() override
	{
		vec = { T(14), T(27), T(83), T(52) };
		expectedVector = { static_cast<R>(0.1365089938063065), static_cast<R>(0.2632673451978768), static_cast<R>(0.809303310060269), static_cast<R>(0.5070336912699849) };
	}
};
TYPED_TEST_SUITE(Vector4DNormalization, SupportedTypes);


template <typename T>
class Vector4DZeroNormalization : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;

	void SetUp() override
	{
		vec = { T(0), T(0), T(0), T(0) };
	}
};
TYPED_TEST_SUITE(Vector4DZeroNormalization, SupportedTypes);


/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/

TEST(VectorInitialization, EmptyConstructorInitializesZeroVector)
{
	// Given a vector initialized without parameters
	const math::Vector4D<float> vec;

	// Then, it's elements form a zero vector
	EXPECT_VEC_ZERO(vec);
}

TYPED_TEST(VectorInitialization, ConstructorInitializesVectorsWithCorrectValue)
{
	// Given 4 different values
	TypeParam a = static_cast<TypeParam>(3);
	TypeParam b = static_cast<TypeParam>(1);
	TypeParam c = static_cast<TypeParam>(6);
	TypeParam d = static_cast<TypeParam>(4);

	// When, a vector is initialized with those values
	const math::Vector4D<TypeParam> vec(a, b, c, d);

	// Then, the values are stored as elements of the vector
	EXPECT_VEQ_CONTAINS(vec, a, b, c, d);
}

TYPED_TEST(VectorInitialization, Two2DVectorsCanInitializeA4DVector)
{
	// Given two 2D Vectors
	TypeParam a = static_cast<TypeParam>(3);
	TypeParam b = static_cast<TypeParam>(1);
	TypeParam c = static_cast<TypeParam>(6);
	TypeParam d = static_cast<TypeParam>(4);
	const math::Vector2D<TypeParam> vec1(a, b);
	const math::Vector2D<TypeParam> vec2(c, d);

	// When a Vector4D is initialized with those vectors
	const math::Vector4D<TypeParam> vec(vec1, vec2);

	// Then, the 2D vector elements form the 4D vector
	EXPECT_VEQ_CONTAINS(vec, a, b, c, d);
}

TYPED_TEST(VectorInitialization, One3DVectorAndScalarCanInitializeA4DVector)
{
	// Given a 3D Vector and a scalar
	TypeParam a = static_cast<TypeParam>(3);
	TypeParam b = static_cast<TypeParam>(1);
	TypeParam c = static_cast<TypeParam>(6);
	const math::Vector3D vec1(a, b, c);
	TypeParam scalar = static_cast<TypeParam>(4);

	// When a Vector4D is initialized with those vectors
	const math::Vector4D vec(vec1, scalar);

	// Then, the 3D vector elements + scalar form the 4D vector in the passed-in format
	EXPECT_VEQ_CONTAINS(vec, a, b, c, scalar);
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

TEST(Vector4DAccess, vec4Return4DFloatVector)
{
	// Given a vector is accessed as vec4
	constexpr bool isCorrectType = std::is_same_v<math::vec4::value_type, float>;

	// Then, it's value_type is float
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, dvec4Return4DDoubleVector)
{
	// Given a vector is accessed as dvec4
	constexpr bool isCorrectType = std::is_same_v<math::dvec4::value_type, double>;

	// Then, it's value_type is double
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, ivec4Return4DIntegerVector)
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

TYPED_TEST(Vector4DAddition, VectorPlusVectorReturnsNewVectorWithSum)
{
	// Given two vectors
	// When they are added together
	const math::Vector4D result = this->vecA + this->vecB;

	// Then the output vector contains sum of elements
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DAddition, VectorPlusEqualsReturnsSameVectorWithSum)
{
	//Given two vectors
	// When one vector is added to the other(+=)
	this->vecA += this->vecB;

	// Then, the original vector contains the sum of the elements added together
	EXPECT_VEC_EQ(this->expected, this->vecA);
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

TYPED_TEST(Vector4DSubtraction, VectorMinusVectorReturnsNewVectorWithDifference)
{
	// Given two vectors
	// When they are added together
	const math::Vector4D result = this->vecA - this->vecB;

	// Then the output vector contains the difference between elements
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DSubtraction, VectorMinusEqualsVectorReturnsSameVectorWithDifference)
{
	//Given two vectors
	// When one vector is added to the other(+=)
	this->vecA -= this->vecB;

	// Then, the original vector contains the difference between elements
	EXPECT_VEC_EQ(this->expected, this->vecA);
}

TEST(Vector4DSubtraction, MixedTypeSubtractionPromotesType)
{
	// Given vectors with arbitrary values
	const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
	const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
	const math::Vector4D expected(-6.0, 5.0, -11.0, -1.0);

	// When they are subtracted
	const math::Vector4D result = vec1 - vec2;

	// Then the new vector is type promoted
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	// And contains difference between the elements
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
	// Given vectors with arbitrary values
	math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
	const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
	const math::Vector4D expected(-6.0, 5.0, -11.0, -1.0);

	// When one vector is subtracted from the other(-=)
	vec1 -= vec2;

	// Then, the original vector's type is preserved
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	// And contains difference between the elements
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector4DScalarMultiplication, VectorTimesZeroReturnsZeroVector)
{
	// Given an arbitrary vector
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// When multiplied with 0
	const math::Vector4D result = vec * 0;

	// Then, we get a zero vector
	EXPECT_VEC_ZERO(result);
}

TEST(Vector4DScalarMultiplication, VectorTimesOneReturnsVectorWithSameValues)
{
	// Given an arbitrary vector
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// When multiplied with 1
	const math::Vector4D result = vec * 1;

	// Then, we get the same vector
	EXPECT_VEC_EQ(vec, result);
}

TYPED_TEST(Vector4DScalarMultiplication, VectorTimesANumberReturnsAScaledVector)
{
	// Given an arbitrary vector and a scalar

	// When multiplied (vec * scalar)
	const math::Vector4D result = this->vec * this->scalar;

	// Then, new vector contains elements multiplied(scaled) with the scalar
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DScalarMultiplication, NumberTimesAVectorReturnsAScaledVector)
{
	// Given an arbitrary vector and a scalar

	// When multiplied (vec * scalar)
	const math::Vector4D result = this->scalar * this->vec;

	// Then, new vector contains elements multiplied(scaled) with the scalar
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DScalarMultiplication, VectorTimesEqualAScalarIsTheSameVectorScaled)
{
	// Given an arbitrary vector and a scalar

	// When multiplied (vec * scalar)
	this->vec *= this->scalar;

	// Then, the original vector is scaled by the scalar
	EXPECT_VEC_EQ(this->expected, this->vec);
}

TEST(Vector4DScalarMultiplication, MixedTypeScalarMulitplicationPromotesType)
{
	// Given a vector and scalar with arbitrary values
	const math::Vector4D vec(3.0f, 0.0f, -1.0f, 2.0f);
	constexpr double scalar = 5.0;
	const math::Vector4D expected(15.0, 0.0, -5.0, 10.0);

	// When they are multiplied
	const math::Vector4D result = vec * scalar;

	// Then the new vector is type promoted
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DScalarMultiplication, MixedTypeScalarMulitplicationAssignmentDoesNotPromoteType)
{
	// Given a vector and scalar with arbitrary values
	math::Vector4D vec(3.0f, 0.0f, -1.0f, 2.0f);
	constexpr double scalar = 5.0;
	const math::Vector4D expected(15.0f, 0.0f, -5.0f, 10.0f);

	// When vector is multiplied by the scalar and assigned (*=)
	vec *= scalar;

	// Then the vector type is preserved
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector4DScalarMultiplication, MixedTypeScalarMulitplicationAssignmentGivesResultWithMinimalPrecisionLoss)
{
	// Given a vector and scalar with arbitrary values
	math::Vector4D vec(3, 0, -1, 8);
	constexpr double scalar = 2.5;
	const math::Vector4D expected(7, 0, -2, 20);

	// When vector is multiplied by the scalar and assigned (*=)
	vec *= scalar;

	// And the vector is scaled by `scalar` with minimal precision loss
	EXPECT_VEC_EQ(expected, vec);
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByZeroReturnsInfinityVector)
{
	// Given an arbitrary vector

	// Floating point
	if constexpr (std::is_floating_point_v<TypeParam>)
	{
		// When divided by zero
		const math::Vector4D result = this->vec / 0;

		// Then, the resultant vector is an infinity vector
		EXPECT_VEC_INF(result);
	} // Integrals
	else
	{
		EXPECT_DEATH({ this->vec / 0; }, "Integral division by zero");
	}
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByOneReturnsAVectorWithSameValues)
{
	// Given an arbitrary vector

	// When divided by one
	const math::Vector4D result = this->vec / 1;

	// Then, the resultant vector is an infinity vector
	EXPECT_VEC_EQ(result, this->vec);
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByANumberReturnsAScaledVector)
{
	// Given an arbitrary vector

	// When divided by a scalar
	const math::Vector4D result = this->vec / this->scalar;

	// Then, the resultant vector is a new vector with elements divided by the scalar
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DScalarDivision, VectorDivideEqualsANumberIsTheSameVectorScaled)
{
	// Given an arbitrary vector

	// When divide equals by a scalar
	this->vec /= this->scalar;

	// Then, the resultant vector is the same vector with elements divided by the scalar
	EXPECT_VEC_EQ(this->expected, this->vec);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisionPromotesType)
{
	// Given an arbitrary vector
	const math::Vector4D vec(15.0, 0.0, -5.0, 10.0);
	constexpr double scalar = 5.0;
	const math::Vector4D expected(3.0f, 0.0f, -1.0f, 2.0f);

	// When divided by a scalar
	const math::Vector4D result = vec / scalar;

	// Then the new vector is type promoted
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisonAssignmentDoesNotPromoteType)
{
	// Given an arbitrary vector
	math::Vector4D vec(15.0f, 0.0f, -5.0f, 10.0f);
	constexpr double scalar = 5.0;

	const math::Vector4D expected(3.0f, 0.0f, -1.0f, 2.0f);

	// When divide equals by a scalar
	vec /= scalar;

	// Then the vector type is preserved
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisionAssignmentGivesResultWithMinimalPrecisionLoss)
{
	// Given an arbitrary vector
	math::Vector4D vec(10, 25, -30, 2);
	constexpr double scalar = 2.5;
	const math::Vector4D expected(4, 10, -12, 0);

	// When vector divides equal by a scalar
	vec /= scalar;

	// And the vector is scaled by `scalar` with minimal precision loss
	EXPECT_VEC_EQ(expected, vec);
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


/***************************************
 *                                     *
 *  MAGNITUDE AND NORMALIZATION TESTS  *
 *                                     *
 ***************************************/

TEST(Vector4DMagnitude, ZeroVectorReturnsZero)
{
	// Given a zero vector
	const math::Vector4D vec(0.0f, 0.0f, 0.0f, 0.0f);

	// When its magnitude is taken
	const float magnitude = vec.mag();

	// Then, zero is returned
	EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector4DMagnitude, VectorWithOneComponentsReturnsNonUnitScalar)
{
	// Given a unit vector
	const math::Vector4D vec(1.0f, 1.0f, 1.0f, 1.0f);

	// When its magnitude is taken
	const float magnitude = vec.mag();

	// Then, non-unit number is returned
	EXPECT_NE(1.0f, magnitude);
}

TYPED_TEST(Vector4DMagnitude, NonUnitVectorReturnsCorrectMagnitude)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = this->vec.mag();

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);
	
}

TYPED_TEST(Vector4DMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = math::Vector4D<TypeParam>::mag(this->vec);

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);
}

TYPED_TEST(Vector4DUncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithPrecision)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = this->vec.mag();

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);
}

TYPED_TEST(Vector4DUncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithPrecision)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = math::Vector4D<TypeParam>::mag(this->vec);

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);
}

TEST(Vector4DNormalization, ZeroVectorWhenNormalizedCausesDeath)
{
	// TODO: Implementation
}

TYPED_TEST(Vector4DNormalization, VectorWhenNormalizedReturnsANormalVector)
{
	// Given a non-normalized vector

	// When it is normalized
	const math::Vector4D normalized = this->vec.normalize();

	// Then, the resultant vector is normalized
	EXPECT_VEC_EQ(this->expectedVector, normalized);
}

//TODO: Change to use wrapper
TYPED_TEST(Vector4DNormalization, StaticWrapper_VectorWhenNormalizedReturnsANormalVector)
{
	// Given a non-normalized vector
	
	// When it is normalized
	const math::Vector4D normalized = math::Vector4D<TypeParam>::normalize(this->vec);

	// Then, the resultant vector is normalized
	EXPECT_VEC_EQ(this->expectedVector, normalized);
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