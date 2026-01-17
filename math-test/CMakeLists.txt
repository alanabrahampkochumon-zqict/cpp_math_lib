add_executable(MathTest)

target_sources(
    MathTest
    PRIVATE
        src/Vector3DTests.cpp
)

target_link_libraries(
    MathTest
    PRIVATE
    MathLib
)