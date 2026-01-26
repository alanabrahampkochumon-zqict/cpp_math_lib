add_executable(MathTest)

function(AppendDirectoryToFiles DirectoryName FileList ResultList)
    set(TempFiles "${${ResultList}}")
    foreach(_FILE ${FileList})
        string(CONCAT FileName ${DirectoryName} ${_FILE})
        list(APPEND TempFiles ${FileName})
    endforeach()
    set(${ResultList} "${TempFiles}" PARENT_SCOPE)
endfunction()

# Vector Test Sources
set(VectorTestDirectory "src/vectors/")
set(VectorTestFiles Vector2DTests.cpp Vector3DTests.cpp Vector4DTests.cpp)
AppendDirectoryToFiles(${VectorTestDirectory} "${VectorTestFiles}" VectorTestSources)

# message(${VectorTestSources})


target_sources(
    MathTest
    PRIVATE
        ${VectorTestSources}
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

