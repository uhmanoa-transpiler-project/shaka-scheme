cmake_minimum_required(VERSION 3.2)
project(shaka-scheme)

################################################################################
# CMAKE DEPENDENCIES
################################################################################
include(ExternalProject)

################################################################################
################################################################################
# CONFIG
################################################################################
################################################################################

# CMake
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

# C++
set(CMAKE_CXX_STANDARD 11)

# Shaka Scheme
set(SHAKA_SCHEME_MAJOR_VERSION 0)
set(SHAKA_SCHEME_MINOR_VERSION 1)
set(SHAKA_SCHEME_LIBRARY_NAME
"shaka-scheme-${SHAKA_SCHEME_MAJOR_VERSION}-$\
{SHAKA_SCHEME_MINOR_VERSION}")
set(SHAKA_SCHEME_REPL_NAME
"shaka-scheme-repl-${SHAKA_SCHEME_MAJOR_VERSION}-$\
{SHAKA_SCHEME_MINOR_VERSION}")

include_directories(./src)

################################################################################
# SHAKE SCHEME DEPENDENCIES
################################################################################
include(config-cmake/dep/boost/boost.cmake)
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

################################################################################
# SHAKA SCHEME
################################################################################
set(SOURCE_FILES main.cpp src/shaka_scheme/system/base/IEnvironment.hpp
        src/shaka_scheme/system/exceptions/BaseException.hpp
        src/shaka_scheme/system/exceptions/InvalidInputException.hpp
        src/shaka_scheme/system/base/Data.cpp src/shaka_scheme/system/exceptions/TypeException.hpp)
add_library(${SHAKA_SCHEME_LIBRARY_NAME} SHARED ${SOURCE_FILES})


################################################################################
# TEST EXTERNAL LIBRARIES
################################################################################
include(config-cmake/dep/googletest/googletest.cmake)

################################################################################
# TESTS
################################################################################
add_subdirectory(tst)

################################################################################
# SHAKA SCHEME REPL
################################################################################
add_executable(${SHAKA_SCHEME_REPL_NAME} ${SOURCE_FILES})
target_link_libraries(${SHAKA_SCHEME_REPL_NAME} ${SHAKA_SCHEME_LIBRARY_NAME})
