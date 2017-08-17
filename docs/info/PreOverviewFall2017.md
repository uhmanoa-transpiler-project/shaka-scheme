#  An Overview of Shaka Scheme's Architecture

## Introduction

Shaka Scheme is a C++11 implementation of the programming 
language Scheme, currently based on the Revised^7 Report on the Algorihtmic 
Language Scheme R7RS).

Our primary source for our implementation model comes from 
"Three Implementation Models for Scheme," by R. Kent. Dybvig (1987) -- 
particularly, the heap-based implementation.

## A Short Overview Of Dybvig's Heap-Based Model

The heap-based model uses 5 registers: the accumulator, the 
next expression, the current environment, the current value rib, and the 
current stack.


