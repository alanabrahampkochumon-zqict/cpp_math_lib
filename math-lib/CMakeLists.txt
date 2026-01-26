add_library(MathLib INTERFACE)

function(AppendDirectoryToFiles DirectoryName FileList ResultList)
    set(TempFiles "${${ResultList}}")
    foreach(_FILE ${FileList})
        string(CONCAT FileName ${DirectoryName} ${_FILE})
        list(APPEND TempFiles ${FileName})
    endforeach()
    set(${ResultList} "${TempFiles}" PARENT_SCOPE)
endfunction()

set(HeaderFiles Vector3D.h Vector2D.h Vector4D.h)
set(TemplateDefinitionFiles Vector2D.tpp Vector3D.tpp Vector4D.tpp)

set(HeaderDirectory "include/")
set(TemplateDefinitionDirectory "include/")

AppendDirectoryToFiles(${HeaderDirectory} "${HeaderFiles}" HeaderSources)
AppendDirectoryToFiles(${TemplateDefinitionDirectory} "${TemplateDefinitionFiles}" TemplateDefinitionSources)

target_sources(
    MathLib

    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS
        include
    FILES
        ${HeaderSources} ${TemplateDefinitionSources}
)

target_include_directories(
    MathLib
    INTERFACE

    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SRC_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"

)


add_custom_target(
    Math
    ALL
    SOURCES
    ${HeaderSources} ${TemplateDefinitionSources}
)

source_group("Templates" FILES ${TemplateDefinitionSources})