# Installing Shaka Scheme Dependencies

Shaka Scheme uses Google Test to build the test cases for the
project. In order to do so, users should:

- Clone the Google Test repository into this folder
- Create a `build` directory in the `googletest/` directory
- Use CMake to generate Unix Makefiles as an out-of-source
  build in the `build` directory.
- Run the Makefiles using GNU Make or another compatible
  tool in order to produce the correct static library `.a`
  files for use with the top-level Makefile for Shaka Scheme.

