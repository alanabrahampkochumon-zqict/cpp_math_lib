include(CheckCXXCompilerFlag)

function (AddSIMDCompilerFlag Target)
    if(MSVC)
        check_cxx_compiler_flag("/arch:AVX" HAS_AVX_SUPPORT)
        check_cxx_compiler_flag("/arch:AVX2" HAS_AVX2_SUPPORT)
        check_cxx_compiler_flag("/arch:AVX512" HAS_AVX512_SUPPORT)

        if(HAS_AVX512_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX512"
            )
            message(STATUS "Enabled AVX512")
        elseif(HAS_AVX2_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX2"
            )
            message(STATUS "Enabled AVX2")
        elseif(HAS_AVX_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX"
            )
            message(STATUS "Enabled AVX")
        elseif(HAS_SSE_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:SSE"
            )
            message(STATUS "Enabling SSE...")
        else()
            message(STATUS "CPU doesn't support SIMD instruction set")
        endif()
    else()
        check_cxx_compiler_flag("-msse4.1" HAS_SSE_SUPPORT)
        check_cxx_compiler_flag("-mavx" HAS_AVX_SUPPORT)
        check_cxx_compiler_flag("-mavx2" HAS_AVX2_SUPPORT)
        check_cxx_compiler_flag("-mavx512f" HAS_AVX512_SUPPORT)

        if(HAS_AVX512_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx512f"
            )
            message(STATUS "Enabled AVX512")
        elseif(HAS_AVX2_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx2"
            )
            message(STATUS "Enabled AVX2")
        elseif(HAS_AVX_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx"
            )
            message(STATUS "Enabled AVX")
        elseif(HAS_SSE_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-msse4.1"
            )
            message(STATUS "Enabling SSE...")
        else()
            message(STATUS "CPU doesn't support SIMD instruction set")
        endif()
    endif()
endfunction(AddSIMDCompilerFlag)