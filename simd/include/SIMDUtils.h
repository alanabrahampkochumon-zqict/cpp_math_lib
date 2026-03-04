#pragma once

#include <bit>
#include <cstddef>

namespace falcon::simd
{
	struct PackedSize
	{
		std::size_t alignedByteSize;
		std::size_t padding;
		std::size_t packedRegisterWidth;
		std::size_t registerCount;
	};

	/**
	 * A simple calculator function that gives Aligned Byte Size, Padding, Packed Register Width, and Register Count
	 * when provided with an unaligned byteSize and maximumAlignment possible.
	 * @param totalByteSize Total unaligned byte size.
	 * @param maxAlignAs Max possible alignment for a given CPU architecture. 16 for SSE, 32 for AVX and AVX2, and 64 for AVX512
	 * @return PackedSize containing alignedByteSize, padding, register width and register count.
	 */
	constexpr PackedSize calculatePackedSize(std::size_t totalByteSize, std::size_t maxAlignAs)
	{
		if (totalByteSize < 16)
			return PackedSize { 16, 16 - totalByteSize, 0, 0 };
		
		const std::size_t packedSize = std::bit_ceil(totalByteSize);

		return PackedSize { packedSize, packedSize - totalByteSize, 0, 0 };
	}
}
