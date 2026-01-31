add_library(MathLib INTERFACE)

set(VectorDirectory "include/vector/")
set(VectorHeaderFiles Vector3D.h Vector2D.h Vector4D.h)
list(TRANSFORM VectorHeaderFiles PREPEND ${VectorDirectory})

set(VectorTemplateDefinitionFiles Vector2D.tpp Vector3D.tpp Vector4D.tpp)
list(TRANSFORM VectorTemplateDefinitionFiles PREPEND ${VectorDirectory})

set(MatrixDirectory "include/matrix/")
set(MatrixHeaderFiles Matrix3D.h)
list(TRANSFORM MatrixHeaderFiles PREPEND ${MatrixDirectory})

set(MatrixTemplateDefinitionFiles Matrix3D.tpp)
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