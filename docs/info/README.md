# Building Shaka Scheme

## Requirements

Building Shaka Scheme requires:

- C++11 enabled compiler (e.g. `g++` or `clang++`)
- `cmake`
- `make`
- Google Test / Google Mock
- Boost C++ Libraries

## Project Structure

- CMake will read its primary input from the top-leve `CMakeLists.txt` file.
    - Other CMake configuration files will be placed in the `./config-cmake`
    directory.
        - Dependency adaptation CMake configuration files will be placed in 
        `dep/DEPENDENCY_NAME`.
- Using CMake, you will choose to build the resulting "build artifacts" in
  a directory of your own -- we recommend creating and running CMake from `
  ./build`.
- Currently,
    - the Shaka Scheme library is setup to be built under `./build/lib/`.
    - the Shaka Scheme REPL is setup to be build under `./build/bin/`.
    - unit and integration tests are setup to be built under `./build/bin/tst/`.
    
## High-Level Source Structure

- Source files will be divided under `./src/`:
    -  `./src/system/` will contain files necessary to supporting the core 
    system implementation. This includes:
        - Numeric types and their data presentation
        - Environment data types
        - Procedure literal data types
        - core Data representation type
     - `./src/corelibs/` will include implementations of primary libraries 
     necessary for standard Scheme operation, such as numeric operations or 
     list manipulation, and IO.
     - `./src/libs/` will contain implementation of libraries that are optional
     for standard Scheme compliance, such as complex math.
     - `./src/auxilary/` will contain non-standard features that are outside of
      the
     Scheme standard, such as debugging functionality, other macro system 
     implementations, and other libraries. It is **not** preferred to place 
     extensions to Shaka Scheme here -- use this as a last resort.
     - `./src/external/` will contain code for external modules or 
     plugin-like functionality that is designed to work with Shaka Scheme. If
      you are developing add-on features for Shaka Scheme, please ensure that
       your code will be able to be hosted here.
       
## Embedding Shaka Scheme Into C++ Programs
Shaka Scheme is meant to be embedded into C++ programs. Therefore, Shaka
Scheme has a C++ API that is meant to be clean and compatible with C++.
    



