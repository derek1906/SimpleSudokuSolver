#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Sudoku.h"

void checkArgs(int argc){
	if(argc != 2){
		printf("Not enough arguments.\n\n\tUsage: ./test file_name\n\n");
		exit(1);
	}
}

void printArgs(int argc, char** args){
	for(int i = 0; i < argc; i++){
		printf("%d:\t%s\n", i, args[i]);
	}
}


int main(int argc, char** args){
	printArgs(argc, args);
	checkArgs(argc);


	Sudoku* sudoku = Sudoku::factory(args[1]);
	if(!sudoku)	exit(1);
	
	sudoku->printBoard();


	return 0;
}