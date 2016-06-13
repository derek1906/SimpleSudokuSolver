#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER
#include "Sudoku.h"

class SudokuSolver{
private:
	Sudoku* sudoku;

public:
	SudokuSolver(Sudoku* sudoku) : sudoku(sudoku);
};


#endif