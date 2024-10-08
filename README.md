# libloadingtip

A C library for low-overhead progress bars and loading tips to display while
stuff happens in the background.

**There is not remotely enough work going into this right now for it to be
considered for production use**.

## Tech Stack
- C11 support at the moment. Need to set up my CI / tooling to ensure everything supports C17 / C20
- [CMake 3.12+](https://cmake.org/) build system 
- [Catch2](https://github.com/catchorg/Catch2) + CTest unit tests for the library functionality
- [UBSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html) +
[AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) linked
against all the unit tests for the debug build.
- GitHub CI workflows for running the test suite with GCC 10 + Clang 14 on Debian

## Contents
If you like this content, my résumé is [here](https://derekrodriguez.dev/resume.pdf)
