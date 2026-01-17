cmake_minimum_required(VERSION 3.23)
project(CPPMathLib)

add_subdirectory(math-lib)
add_subdirectory(playground)
add_subdirectory(math-test)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)