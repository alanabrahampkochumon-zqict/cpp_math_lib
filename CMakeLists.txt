cmake_minimum_required(VERSION 3.23)
project(CPPMathLib)

option(ENABLE_STRICT "Enable ASan and Strict Warnings" OFF) # To turn on ASan, use cmake -D

# Turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enables ASan for all the projects globally.
if(ENABLE_STRICT)
    message("Turning ASan on")
    if(MSVC)
        add_compile_options(/fsanitize=address)
        add_link_options(/fsanitize=address)
    else()
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    endif()
endif()


add_subdirectory(math-lib)
add_subdirectory(playground)
add_subdirectory(test-harness)
add_subdirectory(simd)

include(dependencies.cmake)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)