## 2024 Fall CSE101 PA3

Phil Liu
phzliu
README.md

## Description for PA3

This project implements an algorithm to find the strongly connected components (SCCs) of a directed graph using Kosaraju's algorithm. The program reads a graph from an input file, constructs the graph and its adjacency list, performs depth-first search (DFS), and outputs each SCC to an output file.

## Project Structure

- **List.h**: Header file for the List ADT. It contains the definitions of the list structure and function prototypes for list operations.

- **List.c**: Implementation of the List ADT. This file contains the definitions of all functions declared in `List.h`, including operations for adding, removing, and manipulating elements within the list.

- **Graph.h**: Header file for Graph ADT. It contains the definitions of the graph structure and function prototypes for graph operations.

- **Graph.c**: Implementation of the Graph ADT. This file contains the definitions of all functions declared in `Graph.h`, including operations to add edges and arcs, as well as perform Depth-First Search.

- **GraphTest.c**: A test file for the Graph ADT. This file contains a series of tests that validate the functionality of the graph implementation. It ensures that all graph operations perform as expected.

- **FindComponents.c**: The main file for the input sorting. The program reads a graph from an input file, constructs the graph and its adjacency list, performs depth-first search (DFS), and outputs each strongly connected component to an output file.

- **Makefile**: A build script for compiling the project. It contains rules for compiling and executing the project files.

## Usage

1. **Compilation**: Use the provided `Makefile` to compile the project

- **FindComponents**:

   ```bash
   make
   ./FindComponents <input_file> <output_file>
   make checkFind (optional)

- **GraphTest**:

   ```bash
   make GraphTest
   make checkTest (optional)

- **clean**:

   ```bash
   make clean