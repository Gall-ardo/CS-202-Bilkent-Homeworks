# Homework 2: Heap and AVL Trees

## Description
This is the CS 202 HW 2 assignment for Bilkent University, which includes four programs:

1. **least5.cpp**:
   Implements a min-heap to handle adding elements, removing the top, and querying the least 5 elements without removal.

2. **game.cpp**:
   Simulates a card game where two players, Bobô and Holosko, pick cards from their decks to maximize points. The program calculates the final score using optimal strategies with O(N * log N) efficiency.

3. **prefixsubarray.cpp**:
   Finds the minimum subarray length \( L \) where a permuted array `A[1:L]` has at least `M` indices greater than `B[1:L]`. The solution runs in  O(N * log N * log M)  time.

4. **subarray.cpp**:
   Finds the smallest subarray where `M` elements from the first array `A` are greater than `K` elements from the second array `B`. The program efficiently determines this subarray within O(N * log N) time.



## Installation
1. Ensure you have `g++` installed on your system.
2. Clone this repository or download the project files. Files are designed to work with input files and output files.
3. Open the terminal and navigate to the project directory.

## Usage
1. To build the project, run the following command in the terminal:
   ```bash
   make build
    ```
   This will generate 4 executables: least5, game, subarray, and prefixsubarray.

2. To run any of the executables, run the following command in the terminal:
   ```bash
   ./program_name input_file.txt output_file.txt
   ```

## Cleaning Up
To clean up the compiled executables and object files, use:
```bash
  make clean
```


## Notes:
* Input and Output Files: Ensure the input files are properly formatted and contain the data required for the program to run correctly. The output files will show the program results.
* File Format: Both input and output files must be in .txt format.


