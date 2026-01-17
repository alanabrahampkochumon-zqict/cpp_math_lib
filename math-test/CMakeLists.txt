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
    GTest::gtest_main # googletest
)

enable_testing()

include(GoogleTest)
gtest_discover_tests(MathTest)

