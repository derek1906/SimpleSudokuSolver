#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <list>
#include "Sudoku.h"

/**
 * SudokuSolver class
 * @class
 *
 * This class performs a series of actions in attempt to solve a Sudoku instance.
 * All modifications are in place - supplied Sudoku instance will be changed.
 */
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

	bool solve(bool bruteForce);
};


#endif