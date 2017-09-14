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
"shaka-scheme-${SHAKA_SCHEME_MAJOR_VERSION}.$\
{SHAKA_SCHEME_MINOR_VERSION}")
set(SHAKA_SCHEME_REPL_NAME
"shaka-scheme-repl-${SHAKA_SCHEME_MAJOR_VERSION}.$\
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
set(SOURCE_FILES
        src/shaka_scheme/system/base/Data.cpp
        src/shaka_scheme/system/base/Boolean.cpp
        src/shaka_scheme/system/base/String.cpp
        src/shaka_scheme/system/base/Symbol.cpp
        src/shaka_scheme/system/base/DataPair.cpp
        src/shaka_scheme/system/exceptions/MissingImplementationException.hpp)
add_library(${SHAKA_SCHEME_LIBRARY_NAME} SHARED ${SOURCE_FILES})
target_compile_options(${SHAKA_SCHEME_LIBRARY_NAME} PRIVATE -Wall -Wextra
        -pedantic)
# Copy the shared library DLL/dynamic library file also into the
# bin/tst/ folder so that the tests will also be able to find and link to it.
add_custom_command(TARGET ${SHAKA_SCHEME_LIBRARY_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${SHAKA_SCHEME_LIBRARY_NAME}>
        "${CMAKE_BINARY_DIR}/bin/tst/${CMAKE_SHARED_LIBRARY_PREFIX}${SHAKA_SCHEME_LIBRARY_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")

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
add_executable(${SHAKA_SCHEME_REPL_NAME} ${SOURCE_FILES} main.cpp)
target_link_libraries(${SHAKA_SCHEME_REPL_NAME} ${SHAKA_SCHEME_LIBRARY_NAME})
