#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <list>
#include "Sudoku.h"

class SudokuSolver{
private:
	int cellsRemaining;
	Sudoku* sudoku;
	std::list<int> candidates[Sudoku::DIMENSION][Sudoku::DIMENSION];

private:
	bool solve(int x, int y);
	bool solveNext(int x, int y);
	void buildCandidatesTable();
	bool fillInWithLogic();

public:
	SudokuSolver(Sudoku* sudoku);

	bool solve();
};


#endif