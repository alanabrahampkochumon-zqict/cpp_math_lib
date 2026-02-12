add_library(MathLib INTERFACE)

option(ENABLE_STRICT "Makes Compiler Warnings as Error and Turns on AddressSanitizer" ON)

set(VectorDirectory "include/vector/")
set(VectorHeaderFiles Vector3D.h Vector2D.h Vector4D.h)
list(TRANSFORM VectorHeaderFiles PREPEND ${VectorDirectory})

set(VectorTemplateDefinitionFiles Vector2D.tpp Vector3D.tpp Vector4D.tpp)
list(TRANSFORM VectorTemplateDefinitionFiles PREPEND ${VectorDirectory})

set(MatrixDirectory "include/matrix/")
set(MatrixHeaderFiles Matrix2D.h Matrix3D.h)
list(TRANSFORM MatrixHeaderFiles PREPEND ${MatrixDirectory})

set(MatrixTemplateDefinitionFiles Matrix2D.tpp Matrix3D.tpp)
list(TRANSFORM MatrixTemplateDefinitionFiles PREPEND ${MatrixDirectory})

target_sources(MathLib
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        ${VectorHeaderFiles}
        ${VectorTemplateDefinitionFiles}
        ${MatrixHeaderFiles}
        ${MatrixTemplateDefinitionFiles}
)

target_compile_options(MathLib INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
    $<$<BOOL:${ENABLE_STRICT}>:
        $<$<CXX_COMPILER_ID:MSVC>:/WX;/fsanitize=address>
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Werror;-fsanitize=address>
    >
)

target_link_options(MathLib INTERFACE
    $<$<AND:$<BOOL:${ENABLE_STRICT}>,$<CXX_COMPILER_ID:GNU,Clang>>:-fsanitize=address>
)

target_include_directories(
    MathLib
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"

)

add_custom_target(
    Math
    ALL
    SOURCES
    ${VectorHeaderFiles}
    ${VectorTemplateDefinitionFiles}
    ${MatrixHeaderFiles}
    ${MatrixTemplateDefinitionFiles}
)

source_group("Header Files\\vector" FILES ${VectorHeaderFiles})
source_group("Template Files\\vector" FILES ${VectorTemplateDefinitionFiles})
source_group("Header Files\\matrix" FILES ${MatrixHeaderFiles})
source_group("Template Files\\matrix" FILES ${MatrixTemplateDefinitionFiles})