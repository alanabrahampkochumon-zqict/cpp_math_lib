add_executable(Playground)

target_sources(
    Playground
    PRIVATE
    main.cpp
)

target_link_libraries(
    Playground
    PRIVATE
    MathLib
)