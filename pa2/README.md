## 2024 Fall CSE101 PA2

Phil Liu
phzliu
README.md

## Description for PA2

This project implements a Graph ADT and some associated algorithms in C.

## Project Structure

- **List.h**: Header file for the List ADT. It contains the definitions of the list structure and function prototypes for list operations.

- **List.c**: Implementation of the List ADT. This file contains the definitions of all functions declared in `List.h`, including operations for adding, removing, and manipulating elements within the list.

- **Graph.h**: Header file for Graph ADT.  It contains the definitions of the graph structure and function prototypes for graph operations.

- **Graph.c**: Implementation of the Graph ADT. This file contains the definitions of all functions declared in `Graph.h`, including operations like BST and adding edges.

- **GraphTest.c**: A test suite for the Graph ADT. This file contains a series of tests that validate the functionality of the graph implementation. It ensures that all graph operations perform as expected.

-**FindPath.c**: The main file for finding a path between two verticies. The file calls the BFS function and prints out the shortest path between verticies if it exists after reading from an input file.

- **Makefile**: A build script for compiling the project. It contains rules for compiling and executing the project files.

## Usage

1. **Compilation**: Use the provided `Makefile` to compile the project

- **FindPath**:

   ```bash
   make
   ./FindPath <input_file> <output_file>
   make checkFind (optional)

- **GraphTest**:

   ```bash
   make GraphTest
   make checkTest (optional)

- **clean**:

   ```bash
   make clean