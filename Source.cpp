//Program Name: Sudoku Solver
//Programmer Name: Ahmed Mazloum
//Description: The problem to solve is to solves the creators sudoku board using backtracking
//Date: 8/14/2020
#include <iostream>
#include <fstream>
#include "SudokuSolver.h"

using namespace std;

//	Description:Prints every thing	
//	Pre-Condition:none	
//	Post-Condition:	none 	
void main() {
	SudokuSolver solver;

	solver.createBoard();

	system("pause");
}