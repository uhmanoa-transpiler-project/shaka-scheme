# Working with Shaka Scheme's C++ Test Cases

Shaka Scheme leverages the Google Test framework and
GNU Make to support its test-driven development workflow.

# Overview

- Each `test-NAME.cpp` file is self-contained with its own `main()` function.
- Each source file is expected to be built with:
  - The correct include paths with `-Imy_directory_name`
  - The linking flag for Google Test: `-lgtest`.
- By convention, each source file is built into a corresponding
 `test-NAME.out` file.

# Makefile Convenience Commands

- In the root directory above this `tests/` folder, there
  exists a `Makefile` with the following relevant commands:
  - `test`: Assumes a variable defined `TESTCASE` has been
    exported before-hand in the environment or has been defined
    as an arugment to the `make `command, and is the name of the 
    test case source file without its file-extension suffix.
  - `run-test`: Runs the `TESTCASE` executable file.
  - `tests`: Builds all of the test case source files in the
    `tests/` directory.
  - `clean-tests`: Removes all of the test case executables.

