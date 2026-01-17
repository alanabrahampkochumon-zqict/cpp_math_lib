add_library(MathLib)

target_sources(
    MathLib
    PRIVATE
    src/Vector3D.cpp

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
        include
    FILES
        include/Vector3D.h
)