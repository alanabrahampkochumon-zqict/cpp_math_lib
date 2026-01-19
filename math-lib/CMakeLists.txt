add_library(MathLib INTERFACE)

set(HEADER_FILES
    include/Vector3D.h
)

set(TEMPLATE_FILES
    include/Vector3D.tpp
)

target_sources(
    MathLib

    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS
        include
    FILES
        ${HEADER_FILES} ${TEMPLATE_FILES}
)

target_include_directories(
    MathLib
    INTERFACE

    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SRC_DIR}/include"
    "$<INSTALL_INTERFACE:include"

)

add_custom_target(
    Math
    ALL
    SOURCES
    ${HEADER_FILES} ${TEMPLATE_FILES}
)

source_group("Templates" FILES ${TEMPLATE_FILES})