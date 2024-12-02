# 2024 Fall CSE101 PA7 - Dictionary

Phil Liu  
phzliu  

## Description for PA5

This project implements a Dictionary Abstract Data Type in C++ using a Red-Black Tree. The main components include the main files WordFrequency.cpp, Order.cpp, a Dictionary ADT to store keys and values, and a test file to validate the functionality of the Dictionary.

## Project Structure

- **WordFrequency.cpp**: Main file that takes in a file as input and assigns each word to the dictionary with the number of times it appears in the input as the value.

- **Order.cpp**: Main file that takes in a file as input and then assigns each word alphabetically to the Dictionary with the line in which it is read as the value.

- **Dictionary.h**: Header file for the Dictionary ADT. It defines the Dictionary structure and function prototypes for Dictionary operations.

- **Dictionary.cpp**: Implementation of the Dictionary ADT. This file contains definitions for all functions declared in `Dictionary.h`, including operations for adding, removing, and manipulating elements within the Dictionary.

- **DictionaryTest.cpp**: A test suite for the Dictionary ADT. This file validates the functionality of the Dictionary implementation and checks for error handling in edge cases.

- **Makefile**: A build script for compiling the project. It includes rules for compiling and executing the project files.

## Usage

1. **Compilation**: Use the provided `Makefile` to compile the project.

- **Order**

    ```bash
    make
    ./WordFrequency <input> <output>

- **DictionaryTest**:

   ```bash
   make DictionaryTest
   ./DictionaryTest

- **clean**:

   ```bash
   make clean