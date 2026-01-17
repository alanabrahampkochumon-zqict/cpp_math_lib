# Math Library for C Plus Plus

Math Library build in CPP for Game Engine following Eric Lengyel's [Foundations fo Game Engine Development Series](https://foundationsofgameenginedev.com/)

Project uses CMake as it's build system.

## How to run

1. [Download and Install CMake](https://cmake.org/download/) if you don't have it installed.
2. Generate project files using
    ```bash
        cmake -B build
    ```
3. Run the build using commandline
    ```bash
        cmake --build build
        ./build/playground/Debug/Playground.exe # To Run the playground
        ./build/math-test/Debug/MathTest.exe # To Run the tests
    ```
    OR
    Run it in Visual Studio or your IDE of choice.
