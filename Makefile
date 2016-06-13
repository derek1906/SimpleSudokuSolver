CC=clang++
CFLAGS=-c -Wall -O3 -std=c++11
EXECUTABLE=sudoku_solver

all: main $(SOURCES) 

# Link them all together
main: solver.o Sudoku.o SudokuSolver.o
	$(CC) solver.o Sudoku.o SudokuSolver.o -o $(EXECUTABLE)

# Compile each source file
solver.o: solver.cpp 
	$(CC) $(CFLAGS) solver.cpp

Sudoku.o: Sudoku.cpp
	$(CC) $(CFLAGS) Sudoku.cpp

SudokuSolver.o: SudokuSolver.cpp
	$(CC) $(CFLAGS) SudokuSolver.cpp

# Clean directory
clean:
	rm *.o $(EXECUTABLE)

# Remake
remake: clean all