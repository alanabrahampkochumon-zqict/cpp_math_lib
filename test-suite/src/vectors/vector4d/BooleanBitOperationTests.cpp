#include "Vector4DTestSetup.h"

class BooleanVectorBitOperations : public ::testing::Test
{
protected:
	math::Vector4D<bool> vecA;
	math::Vector4D<bool> vecB;
	math::Vector4D<bool> expectedAnd;
	math::Vector4D<bool> expectedOr;
	math::Vector4D<bool> expectedNotA;

	void SetUp() override
	{
		vecA = { true, false, true, false };
		vecB = { true, true, false, false };
		expectedAnd = { true, false, false, false };
		expectedOr = { true, true, true, false };
		expectedNotA = { false, true, false, true };
	}
};
// TODO: Add Tests