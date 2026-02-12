cmake_minimum_required(VERSION 3.23)
project(CPPMathLib)

option(ENABLE_STRICT "Enable ASan and Strict Warnings" ON) # TODO: Turn off after library is complete

# Turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enables ASan for all the projects globally.
if(ENABLE_STRICT)
    if(MSVC)
        add_compile_options(/fsanitize=address /wd4201)
        add_link_options(/fsanitize=address)
    else()
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    endif()
endif()


add_subdirectory(math-lib)
add_subdirectory(playground)
add_subdirectory(math-test)

include(dependencies.cmake)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)