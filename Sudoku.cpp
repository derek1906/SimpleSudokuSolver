#include "Sudoku.h"

/**
 * Constructor for the Sudoku class.
 */
Sudoku::Sudoku(){
	for(int x = 0; x < DIMENSION; x++){
		for(int y = 0; y < DIMENSION; y++){
			board[x][y] = 0;
		}
	}
}

/**
 * Constructor for the Sudoku class.
 *
 * Accepts a read only file stream for parsing a .sudoku formatted file into the memory.
 */
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

/**
 * Print the Sudoku board.
 */
void Sudoku::printBoard(){
	for(int y = 0; y < DIMENSION; y++){
		int* row = getRow(y);
		printIntArray(row, Sudoku::DIMENSION);

		delete[] row;
	}
}

/**
 * Returns a new int array containing the specified column.
 * Caller should free the returned array.
 */
int* Sudoku::getColumn(int x){
	int* column = new int[9];
	for(int y = 0; y < DIMENSION; y++){
		column[y] = board[x][y];
	}

	return column;
}

/**
 * Returns a new int array containing the specified row.
 * Caller should free the returned array.
 */
int* Sudoku::getRow(int y){
	int* row = new int[9];
	for(int x = 0; x < DIMENSION; x++){
		row[x] = board[x][y];
	}

	return row;
}

/**
 * Returns a new int array containing the 3x3 grid that contains
 * the specified cell.
 * Caller should free the returned array.
 *
 * Note: To access the array as a matrix, refer to this formula:
 *		array[ x*3 + y ]
 *
 */
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

/**
 * Get the content of a cell.
 */
int Sudoku::getCell(int x, int y){
	return board[x][y];
}

/**
 * Set the content of a cell.
 */
void Sudoku::setCell(int x, int y, int value){
	board[x][y] = value;
}

/**
 * Returns true if a value can be filled into a specified location.
 * Will return false the location is not empty (ie not 0).
 * 
 * @param  x     Location to be tested
 * @param  y     Location to be tested
 * @param  value Value to be tested
 * @return       True if valid
 */
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
/**
 * Sudoku factory
 * Generates a Sudoku instance.
 */
Sudoku* Sudoku::factory(){
	return new Sudoku();
}

/**
 * Generates a Sudoku instance by a filename.
 * Will return NULL if file cannot be opened or not valid.
 * 
 * @param  fileName Filename of a .sudoku file
 * @return          A sudoku instance, or NULL if file cannot be opened
 */
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

/**
 * Check for file validity.
 * @param  file A file stream
 * @return      True if file is a valid .sudoku file
 */
bool Sudoku::checkSudokuFileValidity(std::ifstream& file){
	file.seekg(FILE_HEADER_POS);

	std::string line;
	return std::getline(file, line) && line == "sudoku";
}
