#pragma once

// #define FORCE_NO_SIMD // TODO: Update
#define ENABLE_FGM_SHADER_OPERATORS

#include <limits>

#include <gtest/gtest.h>

#include <vector/Vector4D.h>
#include <MathTraits.h>

#include "./utils/VectorUtils.h"

/*****************
 *               *
 *  TEST SETUPS  *
 *               *
 *****************/
using SupportedTypes = ::testing::Types<unsigned char, bool, int, unsigned int, float, double, std::size_t, long long>;
using SupportedArithmeticTypes = ::testing::Types<unsigned char, int, unsigned int, float, double, std::size_t, long long>;
