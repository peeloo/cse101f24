# 2024 Fall CSE101 PA6 - BigInteger and List ADTs

Phil Liu  
phzliu  

## Description for PA6

This project implements a BigInteger and List Abstract Data Types in C++. The main components include a BigInteger ADT for big integer operations, a List ADT for dynamic list management, and test files to validate the functionality of both ADTs.

## Project Structure

- **Arithmetic.cpp**: Main file that takes in two files as input, and performs big integer operations based off the given input file

- **BigInteger.h**: Header file for the BigInteger ADT. It contains the definitions of the BitInteger structure and function prototypes for its operations.

- **BigInteger.cpp**: Implementation of the BigInteger ADT. This file includes all the functions declared in `BigInteger.h`, providing operations for addition, subtraction, multiplication, and more.

- **BigIntegerTest.cpp**: A test suite for the BigInteger ADT. This file contains tests that validate the functionality of the BigInteger implementation, ensuring all operations perform as expected.

- **List.h**: Header file for the List ADT. It defines the list structure and function prototypes for list operations.

- **List.c**: Implementation of the List ADT. This file contains definitions for all functions declared in `List.h`, including operations for adding, removing, and manipulating elements within the list.

- **ListTest.c**: A test suite for the List ADT. This file validates the functionality of the list implementation and checks for error handling in edge cases.

- **Makefile**: A build script for compiling the project. It includes rules for compiling and executing the project files.

## Usage

1. **Compilation**: Use the provided `Makefile` to compile the project.

- **Arithmetic**

    ```bash
    make
    ./Arithmetic <input> <output>

- **BigIntegerTest**:

   ```bash
   make BigIntegerTest
   ./BigIntegerTest

- **ListTest**:

   ```bash
   make ListTest
   ./ListTest

- **clean**:

   ```bash
   make clean