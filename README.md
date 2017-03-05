# Shaka Scheme

This is the repository for the Transpiler Project's Scheme interpreter,
Shaka Scheme.

Shaka Scheme hopes to be fully R7RS Small-compliant.

# Native Technologies

The primary build environment for the project is the `msys2` emulated
POSIX-compatible shell on the Windows 10 platform. The project software should
thus be buildable in any POSIX-compatible that provides the following
pre-requisite technologies/programs:

# Building - Pre-requisite Programs/Technology

You will need the following technologies/programs:

- **C++11 compiler** - `g++` (or similar; preferably the GNU C++ Compiler)
- **GNU Make** `make` - (or similar)
- **Doxygen** `doxygen` - (no alternative)
- **POSIX-compatible environment shell** (preferably, `bash` or `zsh`)
    - On Windows, a suitable substitute is the `msys2` project, which also
      includes a package manager to download common packages.
    - On Mac OS X, common packages can be acquired through Homebrew `brew`.
    - On Linux, defer to your distribution package manager
      (e.g. `yum`, `pacman`, `apt-get`, etc.).

- **Boost.Variant** `<boost/variant.hpp>` (from the Boost C++ Libraries)
- **Google Test** (with the root project directory embedded in the `dep/`
  dependencies directory, and built before starting to build Shaka Scheme).

# Building the REPL

If you are in a POSIX-compatible environment, use `make` to run:

    make

It should create the REPL executable in the `bin/` directory.

# Running the REPL

There is an included `make` command to run the REPL automatically for
quicker testing. Run:

    make run

The program should start and stop in the root directory, even if interrupted
or sent the termination signal.

# Generating the Doxygen Documentation

Doxygen is a source code documentation generation program that is compatible
with C++. It is being adopted for this project to provide a framework for creating
structured in-code documentation.

Go into the `docs/` directory, and then use the `doxygen_config_file` to run the
following command:

    doxygen ../doxygen_config_file

The Doxygen documentation generation settings are already set to the currently
preferred settings.

The documentation generation settings are currently setup to generate HTML and
LaTeX files. They will be generated in the `docs/html/` and `docs/latex/` directories.

# Building the Google Test Test Cases

Google Test is the test case framework being used for the project.

- Each `.cpp` file in the `tests/` directory is automatically built into a
corresponding `.out` file.
- Each `.cpp` file contains its own `main` function, and is therefore a
self-encapsulated program. 
- Each program is linked with the `-lgtest` flag for `g++` and `clang++`.
- The source files for each test case program is also documented with Doxygen.

To build the tests cases in a POSIX-compatible shell, please make sure to first
install Google Test in the `dep/` directory for Shaka Scheme. Then, run the
following command:

    make tests

To genereate the documentation for the test cases:

    cd tests-docs/
    doxygen ../doxygen_config_file_tests

Doxygen will generate the documentation for the entire project, with the test
cases included as additional files. 

To remove the documentation, run:

    make clean-tests-docs

