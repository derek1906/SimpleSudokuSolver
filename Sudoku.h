#ifndef SUDOKU
#define SUDOKU

#define FILE_HEADER_POS 0
#define BOARD_POS 7

class Sudoku{
public:
	static const int DIMENSION = 9;

private:
	int board[DIMENSION][DIMENSION];

public:
	Sudoku();
	Sudoku(std::ifstream& file);

	void printBoard();

	int* getColumn(int x);
	int* getRow(int y);

	void setCell(int x, int y, int value);

private:
	void printIntArray(int* arr, int length);

// static
public:
	static Sudoku* factory();
	static Sudoku* factory(char* fileName);
	static bool checkSudokuFileValidity(std::ifstream& file);
};

#endif