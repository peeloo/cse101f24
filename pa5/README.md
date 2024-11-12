# 2024 Fall CSE101 PA5 - Shuffle and Lists

Phil Liu  
phzliu  

## Description for PA5

This project implements a List Abstract Data Type in C++. The main components include the main file Shuffle.cpp, a List ADT for dynamic list management, and a test file to validate teh functionality of the list.

## Project Structure

- **Shuffle.cpp**: Main file that takes in a number n as input and then shuffles decks with sizes 1 all the way to n while outputting how many shuffles it takes to get back to the sorted deck.

- **List.h**: Header file for the List ADT. It defines the list structure and function prototypes for list operations.

- **List.cpp**: Implementation of the List ADT. This file contains definitions for all functions declared in `List.h`, including operations for adding, removing, and manipulating elements within the list.

- **ListTest.cpp**: A test suite for the List ADT. This file validates the functionality of the list implementation and checks for error handling in edge cases.

- **Makefile**: A build script for compiling the project. It includes rules for compiling and executing the project files.

## Usage

1. **Compilation**: Use the provided `Makefile` to compile the project.

- **Sparse**

    ```bash
    make
    ./Shuffle <deck size>

- **ListTest**:

   ```bash
   make ListTest
   ./ListTest

- **clean**:

   ```bash
   make clean