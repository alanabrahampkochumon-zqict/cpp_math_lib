#pragma once

#include <concepts>
#include <type_traits>
#include <cstddef>

namespace math {

	template <typename T>
	concept IsVector = requires(T v, std::size_t i) {

		typename T::value_type;
		{ v[i] } -> std::convertible_to<typename T::value_type>;
	}&& std::is_arithmetic_v<typename T::value_type>;
}