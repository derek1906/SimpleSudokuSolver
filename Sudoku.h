#ifndef SUDOKU
#define SUDOKU

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define FILE_HEADER_POS 0
#define BOARD_POS 7

/**
 * Sudoku class
 *
 * The Sudoku class holds information of a Sudoku puzzle. This class does not have
 * any solving mechanism.
 */
class Sudoku{
public:
	static const int DIMENSION = 9;

private:
	int board[DIMENSION][DIMENSION];

public:
	Sudoku();
	Sudoku(std::ifstream& file);

	~Sudoku(){
		//printf("Destructing.\n");
	}

	Sudoku& operator=(const Sudoku& other){
		for(int x = 0; x < DIMENSION; x++){
			for(int y = 0; y < DIMENSION; y++){
				board[x][y] = other.board[x][y];
			}
		}

		return *this;
	}

	void printBoard();

	int* getColumn(int x);
	int* getRow(int y);
	int* getContainingGrid(int x, int y);

	int getCell(int x, int y);
	void setCell(int x, int y, int value);

	bool isValueValid(int x, int y, int value);

private:
	void printIntArray(int* arr, int length);

// static
public:
	static Sudoku* factory();
	static Sudoku* factory(char* fileName);
	static bool checkSudokuFileValidity(std::ifstream& file);
};

#endif