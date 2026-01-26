add_library(MathLib INTERFACE)

set(HeaderDirectory "include/")
set(HeaderFiles Vector3D.h Vector2D.h Vector4D.h)
list(TRANSFORM HeaderFiles PREPEND ${HeaderDirectory})

set(TemplateDefinitionDirectory "include/")
set(TemplateDefinitionFiles Vector2D.tpp Vector3D.tpp Vector4D.tpp)
list(TRANSFORM TemplateDefinitionFiles PREPEND ${TemplateDefinitionDirectory})

target_sources(MathLib
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        ${HeaderFiles}
        ${TemplateDefinitionFiles}
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
    ${HeaderFiles} ${TemplateDefinitionFiles}
)

source_group("Template Files" FILES ${TemplateDefinitionFiles})