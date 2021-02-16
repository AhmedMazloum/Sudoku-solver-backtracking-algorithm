#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "SudokuSolver.h"
using namespace std;

//	Description:Opend the file and makes sure it opens correctly
//	Pre-Condition:	none
//	Post-Condition:	File able to open
void SudokuSolver::createBoard() {
	int board[size][size];
	ifstream input;
	string filePath;
	string line;
	int row, col, num;
	int start, end;
	int solveStart, solveEnd;

	start = clock();

	cout << "Enter filepath for input file: ";
	getline(cin, filePath);

	


	ifstream temp(filePath);
	if (!temp.good()) {	//	Making sure outputting to existing file
		cout << "\n\n\tInvalid file path, Exiting program" << endl;
		exit(0);
	}
	else if (temp.peek() == ifstream::traits_type::eof()) {
		cout << "\n\n\tFile is empty, Exiting program" << endl;
		exit(0);
	}

	input.open(filePath);

	while (!input.eof()) {
		string temp;

		getline(input, line);

		if (line == "") {
			break;
		}

		istringstream iss(line);

		iss >> temp;
		row = stoi(temp);

		iss >> temp;
		col = stoi(temp);

		iss >> temp;
		num = stoi(temp);

		board[row][col] = num;

		if (board[row][col] != 0) {
			hints++;
		}
	}

	cout << "Input board" << endl;
	printBoard(board);

	solveStart = clock();

	solveBoard(board, actions);

	solveEnd = clock();
	solveTime = solveEnd - solveStart;

	cout << "Solved Board" << endl;
	printBoard(board);

	printMetrics();

	input.close();

	end = clock();

	runTime = end - start;
}

//	Description: Assigns vlaues to all unassigned locations
//	Pre-Condition: A 2-d array and an int passed by reference
//	Post-Condition:	Assigns values to unassigned locations in a way that meets the sudoku rules
bool SudokuSolver::solveBoard(int board[size][size], int& actions) {
	int row, col;

	if (!findEmpty(board, row, col)) {	//	As board is full
		return true;
	}

	for (int x = 1; x <= size; x++) {	//	Else backtracking to solve
		if (isValid(board, row, col, x)) {
			board[row][col] = x;

			if (solveBoard(board, actions)) {
				actions++;
				return true;
			}

			board[row][col] = NULL;
		}
	}

	return false;
}

//	Description: indicates whether an assigned entry in the specified row matches the given number.
//	Pre-Condition:	2D array and two ints called row and num
//	Post-Condition:	Finds if row matches the given number
bool SudokuSolver::inRow(int board[size][size], int row, int num) {
	for (int col = 0; col < size; col++) {
		if (board[row][col] == num) {	//	If found return true
			return true;
		}
	}

	return false;
}

//	Description:indicates whether an assigned entry in the specified column matches the given number.
//	Pre-Condition:2D array and two ints called row and num
//	Post-Condition:	Finds if col matches the given number	
bool SudokuSolver::inCol(int board[size][size], int col, int num) {
	for (int row = 0; row < size; row++) {
		if (board[row][col] == num) {	//	If found return true;
			return true;
		}
	}

	return false;
}

//	Description:indicate whether an assigned entry within the specified 3x3 box matches the given number.
//	Pre-Condition:2d array and three ints are passed in
//	Post-Condition:	Checks if specified 3x3 box matches the given number
bool SudokuSolver::inSub(int board[size][size], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row + startRow][col + startCol] == num) {	//	If found return true
				return true;
			}
		}
	}

	return false;
}

//	Description:indicate whether it will be legal to assign num to the given row, col location.
//	Pre-Condition:2d array and three ints are passed in
//	Post-Condition:	Checks if the num to the given row, col location is legal	
bool SudokuSolver::isValid(int board[size][size], int row, int col, int num) {
	comparisons++;

	//	If not found in row, column or subGroup
	return !inRow(board, row, num) && !inCol(board, col, num) && !inSub(board, row - row % 3, col - col % 3, num) && board[row][col] == NULL;
}

//	Description:finds an entry in the grid that is still unassigned.
//	Pre-Condition:	2d array and two ints that are passed by reference
//	Post-Condition:	Sees if theres a spot on the gird thats unassigned	
bool SudokuSolver::findEmpty(int board[size][size], int& row, int& col) {
	for (row = 0; row < size; row++) {
		for (col = 0; col < size; col++) {
			if (board[row][col] == NULL) {	//	If empty return true
				return true;
			}
		}
	}
	return false;
}

//	Description: Prints the board correctly
//	Pre-Condition:	A 2d array
//	Post-Condition:	Board prints in the correct format
void SudokuSolver::printBoard(int board[size][size]) {
	cout << "--------------------------" << endl;

	for (int row = 0; row < size; row++) {
		cout << "|";

		for (int col = 0; col < size; col++) {
			if (col == 3 || col == 6) {
				cout << " | ";
			}

			if (board[row][col] == NULL) {
				cout << "  ";
			}
			else {
				cout << board[row][col] << " ";
			}
		}

		cout << "|";

		if (row == 2 || row == 5) {
			cout << endl;

			cout << "|------------------------|";
		}

		cout << endl;
	}

	cout << "--------------------------" << endl;
}

//	Description:Outputs the solved board to file
//	Pre-Condition:An ofstream and a 2d array
//	Post-Condition:	prints the grid to a file	
void SudokuSolver::printFile(ofstream& output, int board[size][size]) {
	output << "--------------------------" << endl;

	for (int row = 0; row < size; row++) {
		output << "|";

		for (int col = 0; col < size; col++) {
			if (col == 3 || col == 6) {
				output << " | ";
			}

			if (board[row][col] == NULL) {
				output << "  ";
			}
			else {
				output << board[row][col] << " ";
			}
		}

		output << "|";

		if (row == 2 || row == 5) {
			output << endl;

			output << "|------------------------|";
		}

		output << endl;
	}

	output << "--------------------------" << endl;
}

//	Description:Prints the metrics 
//	Pre-Condition:none
//	Post-Condition:	Prints the metrics
void SudokuSolver::printMetrics() {
	cout << "\tMetrics" << endl;
	cout << "1. Number of hints: \t\t\t" << hints << endl;
	cout << "2. Number of backtracking actions: \t" << actions << endl;
	cout << "3. Number of comparisons: \t\t" << comparisons << endl;
	cout << "4. Time to solve puzzle: \t\t" << solveTime << endl;
	cout << "5. Time to run program: \t\t" << runTime << endl;
}