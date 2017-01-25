# Shaka Scheme

This is the repository for the Transpiler Project's Scheme interpreter,
Shaka Scheme.

# Native Technologies

The primary build environment is the `msys2` emulated POSIX-compatible shell
on the Windows 10 platform. The project software should thus be buildable
in any POSIX-compatible that provides the following pre-requisite
technologies/programs:

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

Go into the `doc/` directory, and then use the `doxygen_config_file` to run the
following command:

    doxygen ../doxygen_config_file

The Doxygen documentation generation settings are already set to the currently
preferred settings.

The documentation generation settings are currently setup to generate HTML and
LaTeX files. They will be generated in the `doc/html/` and `doc/latex/` directories.

