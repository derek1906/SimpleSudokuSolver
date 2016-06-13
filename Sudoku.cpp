#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "Sudoku.h"

Sudoku::Sudoku(){
	for(int x = 0; x < DIMENSION; x++){
		for(int y = 0; y < DIMENSION; y++){
			board[x][y] = 0;
		}
	}
}

Sudoku::Sudoku(std::ifstream& file){

	file.seekg(BOARD_POS);

	for(int y = 0; y < DIMENSION; y++){
		for(int x = 0; x < DIMENSION; x++){
			char digit = 0;
			while((digit < '0' || digit > '9') && file.get(digit));
			setCell(x, y, digit - '0');
		}
	}
}

void Sudoku::printBoard(){
	for(int y = 0; y < DIMENSION; y++){
		int* row = getRow(y);
		printIntArray(row, Sudoku::DIMENSION);

		delete row;
	}
}


// Caller should free the returned array
int* Sudoku::getColumn(int x){
	int* column = new int[9];
	memcpy(column, board[x], Sudoku::DIMENSION);

	return column;
}

// Caller should free the returned array
int* Sudoku::getRow(int y){
	int* row = new int[9];
	for(int x = 0; x < DIMENSION; x++){
		row[x] = board[x][y];
	}

	return row;
}

void Sudoku::setCell(int x, int y, int value){
	board[x][y] = value;
}


// private
void Sudoku::printIntArray(int* arr, int length){
	std::cout << "[";
	for(int i = 0; i < length; i++){
		printf("%d", arr[i]);
		if(i < length - 1){
			printf(", ");
		}
	}
	std::cout << "]\n";
}


// static
Sudoku* Sudoku::factory(){
	return new Sudoku();
}

Sudoku* Sudoku::factory(char* fileName){
	std::ifstream file;
	file.open(fileName);
	if(file.fail()){
		perror("Uh oh");
		return NULL;
	}

	if(!Sudoku::checkSudokuFileValidity(file)){
		printf("Not a valid file\n");
		return NULL;
	}

	return new Sudoku(file);
}

bool Sudoku::checkSudokuFileValidity(std::ifstream& file){
	file.seekg(FILE_HEADER_POS);

	std::string line;
	return std::getline(file, line) && line == "sudoku";
}
