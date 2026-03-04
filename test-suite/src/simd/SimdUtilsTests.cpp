#include <gtest/gtest.h>
#include <SIMDUtils.h>

struct TestData
{
	std::size_t totalByteSize;
	std::size_t alignAs;
	std::size_t expectedByteSize;
	std::size_t padding;
	std::size_t packedRegisterWidth;
	std::size_t registerCount;
};

class PackedSizeCalculatorParams: public ::testing::TestWithParam<TestData>{};

TEST_P(PackedSizeCalculatorParams, CalculatesCorrectSize)
{
	// Given an arbitrary data type size and total byte size
	const auto [totalByteSize, alignAs, expectedByteSize, expectedPadding, packedRegisterWidth, registerCount] = GetParam();

	// When packed size is calculated
	falcon::simd::PackedSize packedSize = falcon::simd::calculatePackedSize(totalByteSize, alignAs);

	// It gives the nearest packed size and padding
	EXPECT_EQ(expectedByteSize, packedSize.alignedByteSize);
	EXPECT_EQ(expectedPadding, packedSize.padding);
	// TODO: Add expected values to register width and num
}

INSTANTIATE_TEST_SUITE_P(
	PackedSizeCalculatorTests,
	PackedSizeCalculatorParams,
	::testing::Values(
		// SSE
		TestData {1, 16, 16, 15, 16, 1 }, 
		TestData {4, 16,16, 12, 16, 1 },
		TestData {  8, 16,16, 8, 16, 1 },
		TestData { 12,16, 16, 4 , 16, 1},
		TestData { 16, 16,16, 0 , 16, 1},
		TestData {  20,16, 32, 12 , 16 , 2},
		TestData {  24,16, 32, 8, 16, 2 },
		TestData {  32,16, 32, 0 , 16, 2},
		TestData {  48,16, 64, 16 , 16, 4},
		TestData {  56,16, 64, 8, 16, 4 },
		TestData {  64,16, 64, 0 , 16, 4},
		TestData {  72, 16,128, 56 ,16, 8},
		TestData {  80, 16,128, 48 , 16, 8},
		TestData {  128, 16,128, 0 ,16, 8},
		TestData {  192,16, 256, 64 , 16, 16},
		TestData {  256,16, 256, 0 , 16, 16},
		TestData {  512, 16,512, 0 , 16, 32},
		TestData {  777,16, 1024, 247 , 16, 64},
		TestData {  1024,16, 1024, 0, 16, 64 },
		// AVX/AVX2
		TestData { 1, 32, 16, 15, 16, 1 },
		TestData { 4, 32,16, 12, 16, 1 },
		TestData { 8, 32,16, 8, 16, 1 },
		TestData { 12,32, 16, 4 , 16, 1 },
		TestData { 16, 32,16, 0 , 16, 1 },
		TestData { 20,32, 32, 12 , 32 , 1 },
		TestData { 24,32, 32, 8, 32, 1 },
		TestData { 32,32, 32, 0 , 32, 1 },
		TestData { 48,32, 64, 16 , 32, 2 },
		TestData { 56,32, 64, 8, 32, 2 },
		TestData { 64,32, 64, 0 , 32, 2 },
		TestData { 72, 32,128, 56 ,32, 4 },
		TestData { 80, 32,128, 48 , 32, 4 },
		TestData { 128, 32,128, 0 ,32, 4 },
		TestData { 192,32, 256, 64 , 32,  8},
		TestData { 256,32, 256, 0 , 32, 8 },
		TestData { 512, 32,512, 0 , 32, 16 },
		TestData { 777,32, 1024, 247 , 32, 32 },
		TestData { 1024,32, 1024, 0, 32, 32 },
		// AVX512
		TestData { 1, 64, 16, 15, 16, 1 },
		TestData { 4, 64,16, 12, 16, 1 },
		TestData { 8, 64,16, 8, 16, 1 },
		TestData { 12,64, 16, 4 , 16, 1 },
		TestData { 16, 64,16, 0 , 16, 1 },
		TestData { 20,64, 32, 12 , 32 , 1 },
		TestData { 24,64, 32, 8, 32, 1 },
		TestData { 32,64, 32, 0 , 32, 1 },
		TestData { 48,64, 64, 16 , 64, 1 },
		TestData { 56,64, 64, 8, 64, 1 },
		TestData { 64,64, 64, 0 , 64, 1 },
		TestData { 72, 64,128, 56 ,64, 2 },
		TestData { 80, 64,128, 48 , 64, 2 },
		TestData { 128, 64,128, 0 ,64, 2},
		TestData { 192,64, 256, 64 , 64,  4 },
		TestData { 256,64, 256, 0 , 64, 4 },
		TestData { 512, 64,512, 0 , 64, 8 },
		TestData { 777,64, 1024, 247 , 64, 16 },
		TestData { 1024,64, 1024, 0, 64, 16 }

	)
);
