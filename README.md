#Simple Command Line Sudoku Solver
A simple and fast Sudoku solver written C++. The program takes a `.sudoku` file<sup>[1]</sup> and solves it.

1: A `.sudoku` file consists of UTF-8 characters, with "sudoku" in the first 8 bytes:

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