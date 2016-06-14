#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include "Sudoku.h"
#include "SudokuSolver.h"

// Show usage and quit when a set of invalid arguments are received
void showUsageAndQuit(){
	printf("\
\n\
\tUsage: ./sudoku_solver [-b] -s file_name\n\
\n\
\t-b\tEnable dumb mode... I mean pure brute force mode\n\
\n\
\t-s\tSource .sudoku file name\n\
\n\
");
	exit(1);
}

// main
int main(int argc, char** args){
	// settings
	bool bruteForce = false;
	char* source_file_name = NULL;

	// read arguments
	int c;
	while((c = getopt(argc, args, "bs:")) != -1){
		switch(c){
			case 'b':
				bruteForce = true; break;
			case 's':
				source_file_name = optarg; break;
			case '?':
			default:
				showUsageAndQuit();
		}
	}

	// quit if no source file name
	if(!source_file_name)	showUsageAndQuit();


	// create a sudoku instance
	Sudoku* sudoku = Sudoku::factory(source_file_name);
	// quit if a sudoku instance cannot be created
	if(!sudoku)	exit(1);

	// show input sudoku
	printf("Input:\n");
	sudoku->printBoard();
	printf("\n");


	std::clock_t start = std::clock();

	// solve
	SudokuSolver solver(sudoku);
	bool solved = solver.solve(bruteForce);

	std::clock_t end = std::clock();


	// output solved sudoku
	if(solved){
		printf("Solved in %.2f seconds:\n", (end - start)/ (double) CLOCKS_PER_SEC);
		sudoku->printBoard();
	}else{
		printf("Cannot be solved.\n");
	}


	// clean up
	delete sudoku;

	return 0;
}