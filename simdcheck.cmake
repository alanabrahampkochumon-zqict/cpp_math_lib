cmake_host_system_information(
    RESULT CPU_NAME
    QUERY PROCESSOR_NAME
)

set(SIMD_AVX512_PROG "
    #include <immintrin.h>

    int main()
    {
        float data[16] = {0};
        __m512 a = _mm512_setzero_ps();
        _mm512_storeu_ps(data, a);
        return 0;
    }
")

set(SIMD_AVX2_PROG "
    #include <immintrin.h>

    int main() {
        __m256i data = _mm256_setzero_si256();
        __m256i result = _mm256_abs_epi32(data); // AVX2 specific intrinsic for calculating absolute value of integers
        (void)result;
        return 0;
    }
")

set(SIMD_AVX_PROG "
    #include <immintrin.h>

    int main()
    {
        float data[8] = {0};
        __m256 a = _mm256_setzero_ps();
        _mm256_storeu_ps(data, a);
        return 0;
    }
")

set(SIMD_SSE_PROG "
    #include <xmmintrin.h>

    int main()
    {
        float data[4] = {0};
        __m128 a = _mm_setzero_ps();
        _mm_storeu_ps(data, a);
        return 0;
    }
")

# TODO: Change to use include(CheckCXXSourceRuns)
include(CheckCXXSourceRuns)

function(AddSIMDCompilerFlag Target)
    message(STATUS "Running SIMD checks...")
    if(MSVC)
        set(CMAKE_REQUIRED_FLAGS "/arch:AVX512")
            check_cxx_source_runs("${SIMD_AVX512_PROG}" HAS_AVX512_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)
        set(CMAKE_REQUIRED_FLAGS "/arch:AVX2")
            check_cxx_source_runs("${SIMD_AVX2_PROG}" HAS_AVX2_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)
        set(CMAKE_REQUIRED_FLAGS "/arch:AVX")
            check_cxx_source_runs("${SIMD_AVX_PROG}" HAS_AVX_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)
        set(CMAKE_REQUIRED_FLAGS "/arch:SSE2")
            check_cxx_source_runs("${SIMD_SSE_PROG}" HAS_SSE_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)

        if(HAS_AVX512_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX512"
            )
            message(STATUS "${CPU_NAME} supports AVX-512. Enabling AVX-512...")
        elseif(HAS_AVX2_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX2"
            )
            message(STATUS "${CPU_NAME} supports AVX-2. Enabling AVX-2...")
        elseif(HAS_AVX_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX"
            )
            message(STATUS "Enabled AVX")
        elseif(HAS_SSE_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:SSE"
            )
            message(STATUS "${CPU_NAME} supports SSE. Enabling SSE...")
        else()
            message(WARN "${CPU_NAME} doesn't support SIMD instruction set")
        endif()
    else()
        set(CMAKE_REQUIRED_FLAGS "-mavx512f")
            check_cxx_source_runs("${SIMD_AVX512_PROG}" HAS_AVX512_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)
        set(CMAKE_REQUIRED_FLAGS "-mavx2")
            check_cxx_source_runs("${SIMD_AVX2_PROG}" HAS_AVX2_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)
        set(CMAKE_REQUIRED_FLAGS "-mavx")
            check_cxx_source_runs("${SIMD_AVX_PROG}" HAS_AVX_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)
        set(CMAKE_REQUIRED_FLAGS "-msse4.2")
            check_cxx_source_runs("${SIMD_SSE_PROG}" HAS_SSE_SUPPORT)
        unset(CMAKE_REQUIRED_FLAGS)

        if(HAS_AVX512_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx512f"
            )
            message(STATUS "${CPU_NAME} supports AVX-512. Enabling AVX-512...")
        elseif(HAS_AVX2_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx2"
            )
            message(STATUS "${CPU_NAME} supports AVX-2. Enabling AVX-2...")
        elseif(HAS_AVX_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx"
            )
            message(STATUS "${CPU_NAME} supports AVX. Enabling AVX...")
        elseif(HAS_SSE_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-msse4.2"
            )
            message(STATUS "${CPU_NAME} supports SSE. Enabling SSE...")
        else()
            message(WARN "${CPU_NAME} doesn't support SIMD instruction set")
        endif()
    endif(MSVC)
endfunction(AddSIMDCompilerFlag)


# include(CheckCXXCompilerFlag)

# function (AddSIMDCompilerFlag Target)
#     if(MSVC)
#         check_cxx_compiler_flag("/arch:AVX" HAS_AVX_SUPPORT)
#         check_cxx_compiler_flag("/arch:AVX2" HAS_AVX2_SUPPORT)
#         check_cxx_compiler_flag("/arch:AVX512" HAS_AVX512_SUPPORT)

#         if(HAS_AVX512_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "/arch:AVX512"
#             )
#             message(STATUS "Enabled AVX512")
#         elseif(HAS_AVX2_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "/arch:AVX2"
#             )
#             message(STATUS "Enabled AVX2")
#         elseif(HAS_AVX_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "/arch:AVX"
#             )
#             message(STATUS "Enabled AVX")
#         elseif(HAS_SSE_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "/arch:SSE"
#             )
#             message(STATUS "Enabling SSE...")
#         else()
#             message(STATUS "CPU doesn't support SIMD instruction set")
#         endif()
#     else()
#         check_cxx_compiler_flag("-msse4.1" HAS_SSE_SUPPORT)
#         check_cxx_compiler_flag("-mavx" HAS_AVX_SUPPORT)
#         check_cxx_compiler_flag("-mavx2" HAS_AVX2_SUPPORT)
#         check_cxx_compiler_flag("-mavx512f" HAS_AVX512_SUPPORT)

#         if(HAS_AVX512_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "-mavx512f"
#             )
#             message(STATUS "Enabled AVX512")
#         elseif(HAS_AVX2_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "-mavx2"
#             )
#             message(STATUS "Enabled AVX2")
#         elseif(HAS_AVX_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "-mavx"
#             )
#             message(STATUS "Enabled AVX")
#         elseif(HAS_SSE_SUPPORT)
#             target_compile_options(
#                 ${Target} PRIVATE "-msse4.1"
#             )
#             message(STATUS "Enabling SSE...")
#         else()
#             message(STATUS "CPU doesn't support SIMD instruction set")
#         endif()
#     endif()
# endfunction(AddSIMDCompilerFlag)

