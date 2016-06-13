CC=clang++
CFLAGS=-c -Wall -g -O3
EXECUTABLE=test

all: main $(SOURCES) 

# Link them all together
main: test.o Sudoku.o SudokuSolver.o
	$(CC) test.o Sudoku.o SudokuSolver.o -o $(EXECUTABLE)

# Compile each source file
test.o: test.cpp 
	$(CC) $(CFLAGS) test.cpp

Sudoku.o: Sudoku.cpp
	$(CC) $(CFLAGS) Sudoku.cpp

SudokuSolver.o: SudokuSolver.cpp
	$(CC) $(CFLAGS) SudokuSolver.cpp

# Clean directory
clean:
	rm *o $(EXECUTABLE)
