#include "SudokuSolver.h"

/**
 * Constructor
 * Requires a Sudoku instance
 */
SudokuSolver::SudokuSolver(Sudoku* sudoku) : sudoku(sudoku){
	cellsRemaining = 0;

	for(int x = 0; x < Sudoku::DIMENSION; x++){
		for(int y = 0; y < Sudoku::DIMENSION; y++){
			if(sudoku->getCell(x, y) == 0)	cellsRemaining++;
		}
	}
}

/**
 * buildCandidatesTable populate the candidates matrix with possible valid numbers
 * for all cells in the sudoku puzzle.
 */
void SudokuSolver::buildCandidatesTable(){
	for(int x = 0; x < Sudoku::DIMENSION; x++){
		for(int y = 0; y < Sudoku::DIMENSION; y++){
			candidates[x][y].clear();
			for(int i = 1; i <= 9; i++){
				if(sudoku->isValueValid(x, y, i)){
					candidates[x][y].push_front(i);
				}
			}
		}
	}
}

/**
 * fillInWithLogic attemps to fill in cells that has only a signle possible
 * candidate.
 *
 * @return True if at least one cell is filled.
 */
bool SudokuSolver::fillInWithLogic(){
	bool updated = false;

	for(int x = 0; x < Sudoku::DIMENSION; x++){
		for(int y = 0; y < Sudoku::DIMENSION; y++){
			std::list<int> candidateList = candidates[x][y];
			int candidatesNum = candidateList.size();

			if(candidatesNum == 1){
				sudoku->setCell(x, y, candidateList.front());
				candidateList.pop_front();
				updated = true;
				cellsRemaining--;
			}
		}
	}

	return updated;
}

/**
 * Algorithm to in attempt to solve the sudoku by backtracking. The algorithm
 * will continuously pick candidates from the candidates matrix and fill them
 * into the sudoku until either it solves the sudoku or no more can be filled
 * in without making the sudoku invalid.
 * 
 * @param  x Current cell's x
 * @param  y Current cell's y
 * @return   True if the sudoku can be solved
 */
bool SudokuSolver::solve(int x, int y){
	// solved
	if(!cellsRemaining){
		return true;
	}

	// cannot be solved
	if(x == Sudoku::DIMENSION || y == Sudoku::DIMENSION)	return false;

	// does not need solving
	if(sudoku->getCell(x, y) != 0){
		return solveNext(x, y);
	}


	// get candidates
	std::list<int> candidateList = candidates[x][y];

	// no candidates
	if(!candidateList.size())	return false;

	for(auto itr = candidateList.begin(); itr != candidateList.end(); itr++){
		sudoku->setCell(x, y, *itr);
		cellsRemaining--;

		bool solvable = solveNext(x, y);

		if(solvable){
			// solved
			return true;
		}else{
			// try the next candidate
			cellsRemaining++;
		}
	}

	// not solvable
	sudoku->setCell(x, y, 0);

	return false;
}

/**
 * A wrapper for the recursive solve method.
 * 
 * @param  bruteForce True if the algorithm shall not attempt to solve the puzzle by logic
 * @return            True if the sudoku can be solved (with at least one solution)
 */
bool SudokuSolver::solve(bool bruteForce){
	if(!bruteForce){
		// try solving with logic
		do{
			buildCandidatesTable();
		}while(fillInWithLogic());

		printf("%d cells remaining with pure deduction.\n", cellsRemaining);
	}

	// backtracking
	buildCandidatesTable();
	return solve(0, 0);
}

/**
 * A helper function for the solve method in recursively calling iteself.
 * 
 * @param  x Current cell's x
 * @param  y Current cell's y
 * @return   True if the sudoku can be solved
 */
bool SudokuSolver::solveNext(int x, int y){
	y++;
	if(y == Sudoku::DIMENSION){
		y = 0; x++;
	}

	buildCandidatesTable();
	return solve(x, y);
}