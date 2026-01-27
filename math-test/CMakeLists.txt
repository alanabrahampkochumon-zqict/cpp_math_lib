add_executable(MathTest)

# Vector Test Sources
set(VectorTestDirectory "src/vector/")
set(VectorTestFiles Vector2DTests.cpp Vector3DTests.cpp Vector4DTests.cpp)
list(TRANSFORM VectorTestFiles PREPEND ${VectorTestDirectory})

# Matrix Test Sources
set(MatrixTestDirectory "src/matrix/")
set(MatrixTestFiles Matrix3DTests.cpp)
list(TRANSFORM MatrixTestFiles PREPEND ${MatrixTestDirectory})

# message(${VectorTestSources})


target_sources(
    MathTest
    PRIVATE
        ${VectorTestFiles} ${MatrixTestFiles}
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

