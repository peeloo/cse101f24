## Phil Liu
## phzliu
## 2024 Fall CSE101 PA1
## README.md
## README for PA1

This project implements a lexical sorterusing a doubly linked list data structure in C. 
The main components include a list ADT, a test file for the list, and a lexer that reads from an input file and returns the sorted input to an output file.

## Project Structure

- **List.h**: Header file for the List ADT. It contains the definitions of the list structure and function prototypes for list operations.

- **List.c**: Implementation of the List ADT. This file contains the definitions of all functions declared in `List.h`, including operations for adding, removing, and manipulating elements within the list.

- **ListTest.c**: A test suite for the List ADT. This file contains a series of tests that validate the functionality of the list implementation. It ensures that all list operations perform as expected and checks for error handling in edge cases.

- **Lex.c**: The main file for the input sorting. This program reads input from a specified file, processes the data into tokens, sorts them using the List ADT, and writes the sorted output to a specified output file.

- **Makefile**: A build script for compiling the project. It contains rules for compiling and executing the project files.

## Usage

1. **Compilation**: Use the provided `Makefile` to compile the project

- **Lex**:

   ```bash
   make
   ./Lex <input_file> <output_file>
   make checkLex (optional)

- **ListTest**:

   ```bash
   make ListTest
   make checkTest (optional)

- **clean**:

   ```bash
   make clean