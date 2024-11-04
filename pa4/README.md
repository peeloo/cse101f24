# 2024 Fall CSE101 PA4 - Matrix and List ADTs

Phil Liu  
phzliu  

## Description for PA4

This project implements a Matrix and List Abstract Data Types (ADTs) in C. The main components include a Matrix ADT for matrix operations, a List ADT for dynamic list management, and test files to validate the functionality of both ADTs.

## Project Structure

- **Sparse.c**: Main file that takes in two files as input, and performs Matrix operations based off the given input file

- **Matrix.h**: Header file for the Matrix ADT. It contains the definitions of the matrix structure and function prototypes for matrix operations.

- **Matrix.c**: Implementation of the Matrix ADT. This file includes all the functions declared in `Matrix.h`, providing operations for matrix addition, subtraction, multiplication, and more.

- **MatrixTest.c**: A test suite for the Matrix ADT. This file contains tests that validate the functionality of the matrix implementation, ensuring all matrix operations perform as expected.

- **List.h**: Header file for the List ADT. It defines the list structure and function prototypes for list operations.

- **List.c**: Implementation of the List ADT. This file contains definitions for all functions declared in `List.h`, including operations for adding, removing, and manipulating elements within the list.

- **ListTest.c**: A test suite for the List ADT. This file validates the functionality of the list implementation and checks for error handling in edge cases.

- **Makefile**: A build script for compiling the project. It includes rules for compiling and executing the project files.

## Usage

1. **Compilation**: Use the provided `Makefile` to compile the project.

- **Sparse**

    ```bash
    make
    ./Sparse <input> <output>

- **Matrix**:

   ```bash
   make
   ./MatrixTest  # Run tests for the Matrix ADT

- **ListTest**:

   ```bash
   make ListTest
   make checkTest (optional)

- **clean**:

   ```bash
   make clean