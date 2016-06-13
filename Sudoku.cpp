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

		delete[] row;
	}
}


// Caller should free the returned array
int* Sudoku::getColumn(int x){
	int* column = new int[9];
	for(int y = 0; y < DIMENSION; y++){
		column[y] = board[x][y];
	}

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

// Caller should free the returned array
int* Sudoku::getContainingGrid(int x, int y){
	int ax = (x/3)*3, ay = (y/3)*3,
		bx = (x/3 + 1)*3, by = (y/3 + 1)*3;

	int* grid = new int[9];
	for(int x = ax; x < bx; x++){
		for(int y = ay; y < by; y++){
			grid[(x - ax)*3 + (y-ay)] = board[x][y];
		}
	}

	return grid;
}

int Sudoku::getCell(int x, int y){
	return board[x][y];
}

void Sudoku::setCell(int x, int y, int value){
	board[x][y] = value;
}


bool Sudoku::isValueValid(int x, int y, int value){
	if(getCell(x, y) != 0)	return false;

	// check row and column
	int* col = getColumn(x);
	int* row = getRow(y);
	for(int i = 0; i < DIMENSION; i++){
		if(col[i] == value || row[i] == value){
			delete[] col;
			delete[] row;
			return false;
		}
	}

	// check containing grid
	int* grid = getContainingGrid(x, y);
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			if(grid[x*3 + y] == value){
				delete[] col;
				delete[] row;
				delete[] grid;
				return false;
			}
		}
	}

	delete[] col;
	delete[] row;
	delete[] grid;

	return true;
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
