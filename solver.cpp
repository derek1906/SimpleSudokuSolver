#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>
#include "Sudoku.h"
#include "SudokuSolver.h"

void checkArgs(int argc){
	if(argc != 2){
		printf("Not enough arguments.\n\n\tUsage: ./sudoku_solver file_name\n\n");
		exit(1);
	}
}

int main(int argc, char** args){
	checkArgs(argc);

	Sudoku* sudoku = Sudoku::factory(args[1]);
	if(!sudoku)	exit(1);

	printf("Input:\n");
	sudoku->printBoard();
	std::cout << std::endl;


	std::clock_t start = std::clock();

	SudokuSolver solver(sudoku);
	bool solved = solver.solve();

	std::clock_t end = std::clock();


	if(solved){
		printf("Solved in %.2f seconds:\n", (end - start)/ (double) CLOCKS_PER_SEC);
		sudoku->printBoard();
	}else{
		printf("Cannot be solved.\n");
	}


	delete sudoku;

	return 0;
}