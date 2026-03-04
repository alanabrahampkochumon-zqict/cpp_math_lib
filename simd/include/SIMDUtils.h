#pragma once

#include <bit>
#include <cstddef>

namespace falcon::simd
{
	struct PackedSize
	{
		std::size_t alignedByteSize;
		std::size_t padding;
	};

	constexpr PackedSize calculatePackedSize(std::size_t totalByteSize)
	{
		if (totalByteSize < 16)
			return PackedSize { 16, 16 - totalByteSize };
		
		const std::size_t packedSize = std::bit_ceil(totalByteSize);

		return PackedSize { packedSize, packedSize - totalByteSize };
	}
}
