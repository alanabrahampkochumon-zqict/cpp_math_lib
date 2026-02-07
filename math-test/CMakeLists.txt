add_executable(MathTest)

# Vector Test Sources
set(VectorTestDirectory "src/vector/")
set(VectorTestFiles Vector2DTests.cpp Vector3DTests.cpp Vector4DTests.cpp)
list(TRANSFORM VectorTestFiles PREPEND ${VectorTestDirectory})

# Matrix Test Sources
set(MatrixTestDirectory "src/matrix/")
set(MatrixTestFiles Matrix3DTests.cpp)
list(TRANSFORM MatrixTestFiles PREPEND ${MatrixTestDirectory})

set(UtilityDirectory "src/utils/")
set(Utilities "FloatEquals.h;MatrixUtils.h")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

target_sources(
    MathTest
    PRIVATE
        ${VectorTestFiles} ${MatrixTestFiles} ${Utilities}
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

