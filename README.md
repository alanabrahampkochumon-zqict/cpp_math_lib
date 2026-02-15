# Math Library for CPP

Math Library build in CPP for Game Engine following Eric Lengyel's <a href="https://foundationsofgameenginedev.com/" target="_blank">Foundations fo Game Engine Development Series</a>

Project uses CMake as it's build system.

## How to run

1. Download and install <a href="https://cmake.org/download/" target="_blank">CMake</a> and <a href="https://git-scm.com/install/windows" target="_blank">Git</a> if you don't have it installed.

2. Generate project files using
    ```bash
        cmake -B build
    ```
    OR using
    ```bash
        genStrict.bat
    ```
3. Run the build using commandline
    ```bash
        cmake --build build
        ./build/playground/Debug/Playground.exe # To Run the playground
        ./build/math-test/Debug/MathTest.exe # To Run the tests
    ```
    OR
    Run it in Visual Studio or your IDE of choice.
