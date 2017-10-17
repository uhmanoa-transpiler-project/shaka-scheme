# Shaka Scheme

**Shaka Scheme** is currently a partially-compliant R7RS Scheme implementation written in classic object-oriented
programming (OOP), modern C++ (meaning, C++11 and possibly up).

Its development is fueled by a small team of student developers at University of Hawai'i at Manoa.

## Objectives

The goal for Shaka Scheme is to create a **clean** implementation of R7RS-small Scheme using modern
C++ and OOP design idioms and feature while keeping it readable for novice/intermediate C++ programmers.

However, we also strive to create a stand-alone distribution of Scheme that is relatively light and portable.
Therefore, our design choices tend away from using larger libraries such as Boost within our implementation.

## Tested Platforms

We develop Shaka Scheme across the following compilers:

- Windows - MinGW-w64, MSYS GCC
- Mac OS X - Clang
- Linux - GCC

## Current News

- We are in the process of rewriting the system to support `syntax-rules` macros and `call/cc`.
- We are also in the process of implementing the heap-based virtual machine and compiler pair as
  described in "Three Implementation Models for Scheme" (Dybvig).
- We are also currently in the design phase for a `Context` C++ FFI object to allow the embedding
  of Shaka Scheme itself into C++ programs.
