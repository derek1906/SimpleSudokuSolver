# Simple Command Line Sudoku Solver
A simple and fast Sudoku solver written in C++. The program takes a `.sudoku` file and solves it.

## The `.sudoku` format
A `.sudoku` file consists of UTF-8 characters, with "sudoku" in the first 8 bytes:

	sudoku
	000580026
	026000090
	000000005
	008709000
	700060009
	000104200
	600000000
	080000170
	290031000

`0`'s represents unknown values.

## Compiling the binary
Run the following in the directory:

    make

By default it uses clang++ for compiling.

## Running the binary
The program has the following arguments:

    ./sudoku_solver [-b] -s source_file_path

 - `-b` Brute force mode (slow)
 - `-s` Specify path to source file
