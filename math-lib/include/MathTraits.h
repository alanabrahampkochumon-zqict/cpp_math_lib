#pragma once

#include <concepts>
#include <type_traits>
#include <cstddef>

namespace math {

	template<typename T>
	concept arithmetic = std::integral<T> || std::floating_point<T>;

	template<typename T>
	concept weak_arithmetic = std::is_arithmetic_v<std::decay_t<T>>;

	// Vector requires a value_type, dimension, [] accessor and be its value type needs to be of arithmetic.
	template <typename T>
	concept IsVector = requires(T v, std::size_t i) {
		typename T::value_type;
		{ T::dimension } -> std::same_as<const std::size_t&>;
		{ v[i] } -> std::convertible_to<typename T::value_type>;
	}&& arithmetic<typename T::value_type>;

}