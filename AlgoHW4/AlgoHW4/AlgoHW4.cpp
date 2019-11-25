// Collin Broderick, Praise Eteng, Siddhant Banerjee
/* Questions
1. ForwardElimination fails to provide a solution to the given system because after it iterates through the second row of the matrix, the pivot position's
value becomes 0. When the algorithm tries to iterate through the third row, it will divide its elements by the pivot position value of 0, which will result
in a divide by 0 error and the algorithm will terminate.
BetterForwardElimination remedies this by swapping the pivot row with the row with the greatest value for a pivot position, preventing divide by 0 errors
in the case where the system has a solution.
2. BetterForwardElimination fails to provide a solution for the given system because it continues to iterate through the matrix when the solution is reached,
preventing a correct answer from being reached. The way to remedy this is to check if there is a combination of 0 elements in the first n positions in each
row such that the rows can be ordered to form an upper triangular matrix.
*/


// Applies Guass-Jordan elimination on a matrix
// A: The matrix of coefficients
// b: The system's right-hand side values
// Returns the solved matrix
using namespace std;
#include <malloc.h>
#include <vector>
#include <iostream>
vector< vector<double> > Elimination (vector<vector<double> > A, vector<double> b) {
	double n = A.size(); // The rows of the matrix
	for (int i = 0; i < n; i++) {
		A.at(i).push_back(b.at(i));
	}
	for (int i = 0; i < n - 1; i++) { // Forwards elimination
		bool solved = false;
		int count = 0;
		for (int j = n - 1; j > 0; j--) {
			if (A[j][i] == 0) {
				count++;
			}
			else break;
		}
		if (count > n - 2) solved = true;
		if (!solved) {
			double pivotrow = i;
			for (int j = i + 1; j < n; j++) {
				if (A[j][i] > A[pivotrow][i]) pivotrow = j;
			}
			for (int k = i; k < n + 1; k++) {
				double temp1 = A[i][k];
				double temp2 = A[pivotrow][k];
				A[i][k] = temp2;
				A[pivotrow][k] = temp1;
			}
			for (int j = i + 1; j < n; j++) {
				double temp = (double)A[j][i] / (double)A[i][i];
				for (double k = i; k < n + 1; k++) {
					A[j][k] = A[j][k] - (double)A[i][k] * temp;
				}
			}
		}
	}
	
	for (int i = n - 1; i > 0; i--) { // Backwards elimination
		double diagonal = A[i][i];
		if (diagonal != 0) {
			for (int j = 0; j < i; j++) {
				double ratio = A[j][i] / A[i][i];
				A[j][i] = A[j][i] - ratio * A[i][i];
				A[j][n] = A[j][n] - ratio * A[i][n];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		double diagonal = A[i][i];
		if (diagonal != 0) {
			for (int j = 0; j < n + 1; j++) {
				if (A[i][j] != 0) A[i][j] /= diagonal;
			}
		}
	}
	return A;
}

// Performs guass-jordan elimination on a given matrix and prints the result
// A: The matrix of coefficients
// b: The system's right-hand side values
void elimAndPrint(vector<vector<double>> A, vector<double> b) {
	int n = A.size();
	cout << "Original matrix:" << endl;
	for (int j = 0; j < n; j++) { // print original matrix
		for (int k = 0; k < n + 1; k++) {
			if (k < n) {
				cout << A[j][k] << " ";
			}
			else cout << b[j] << " ";
			
		}
		cout << endl;
	}
	cout << endl;
	vector<vector<double>> result = Elimination(A, b);
	cout << "Solved matrix:" << endl;
	for (int j = 0; j < n; j++) { // print solved matrix
		for (int k = 0; k < n + 1; k++) {
			cout << result[j][k] << " ";
		}
		cout << endl;
	}
}

vector<vector<int>> board = { {79, 71, 18, 20, 34, 51, 93, 65}, {73, 38, 24, 49, 18, 6, 40, 74}, {31, 5, 63, 10, 32, 40, 14, 13}, {13, 78, 48, 19, 78, 11, 90, 94}, {22, 93, 68, 11, 56, 63, 49, 35}, {85, 52, 27, 5, 94, 91, 82, 62}, {46, 23, 99, 77, 10, 42, 1, 72}, {89, 70, 73, 83, 90, 22, 44, 92} };
vector<vector<int>> vals = { {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}  ,{0,0,0,0,0,0,0,0},  {0,0,0,0,0,0,0,0} }; // Matrix of calculated values

// Calculates the value at a given row and column
// r: The row
// c: The column
int calcVal(int r, int c) {
		if (r == 7) vals[r][c] = board[r][c]; // base case for top row
		else if (vals[r][c] == 0) { // not yet calculated
			int up = 0;
			int right = 0;
			int left = 0;
			switch (c) { // checking for if on left/right
			case(0): // left wall
				up = calcVal(r + 1, c);
				right = calcVal(r + 1, c + 1);
				vals[r][c] = board[r][c] + fmax(up, right);
				break;
			case(7): // right wall
				up = calcVal(r + 1, c);
				left = calcVal(r + 1, c - 1);
				vals[r][c] = board[r][c] + fmax(up, left);
				break;
			default: // otherwise
				up = calcVal(r + 1, c);
				left = calcVal(r + 1, c - 1);
				right = calcVal(r + 1, c + 1);
				vals[r][c] = board[r][c] + fmax(fmax(up, left), fmax(up, right));
				break;
			}
		}
		return vals[r][c];
}

// Calculates the optimal path for a starting node
// r: The starting row
// c: The starting column
vector<int> calcPath(int r, int c) {
	vector<int> output = { board[r][c] };
	if (r == 7) { // base case
		return output;
	}
	else {
		int up = 0;
		int right = 0;
		int left = 0;
		vector<int> path;
		switch (c) { // checking for if on left/right
		case(0): // left wall
			up = calcVal(r + 1, c);
			right = calcVal(r + 1, c + 1);
			if (up > right) {
				path = calcPath(r + 1, c);
			}
			else path = calcPath(r + 1, c + 1);
			break;
		case(7): // right wall
			up = calcVal(r + 1, c);
			left = calcVal(r + 1, c - 1);
			if (up > left) {
				path = calcPath(r + 1, c);
			}
			else path = calcPath(r + 1, c - 1);
			break;
		default: // otherwise
			up = calcVal(r + 1, c);
			left = calcVal(r + 1, c - 1);
			right = calcVal(r + 1, c + 1);
			int max = fmax(fmax(up, left), fmax(up, right));
			if (max == up) path = calcPath(r + 1, c);
			else if (max == left) path = calcPath(r + 1, c - 1);
			else if (max == right) path = calcPath(r + 1, c + 1);
			break;
		}
		output.insert(output.begin(), path.begin(), path.end());
		return output;
	}
}

// Calculates the path for question 4
void pathCalculator() {
	vector<vector<int>> paths = { {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}  ,{0,0,0,0,0,0,0,0},  {0,0,0,0,0,0,0,0} };// the paths for each vault index
	vector<int> totals = { 0,0,0,0,0,0,0,0 };
	for (int i = 0; i < 8; i++) { // Calculate path for each starting node

		totals[i] = calcVal(0, i);
		paths[i] = calcPath(0, i);
	}
	cout << "Starting square: Row 1 vault 7" << endl;
	cout << "Bilbo's path: ";
	for (int i = 7; i >= 0; i--) {
		cout << paths[6][i] << " ";
	}
	cout << endl;
	cout << "Total gems collected: " << totals[6] << endl;
	cout << "Arkenstone vault: Row 8 vault 5";
}


int main() {
	vector<vector<double>> A1 = { {1, 1, -1}, {0, 1, 3}, {-1, 0, 2} };	
	vector<double> b1 = { 9, 3, 2 };
	vector<vector<double>> A2 = { {1, 1, 1}, {1, 1, 2}, {2, 2, 3} };
	vector<double> b2 = { 6, 9, 15 };
	vector<vector<double>> A3 = { {1,1,1,1,1,1,1,1}, {1,2,1,1,1,1,2,1}, {1,1,3,1,1,3,1,1}, {1,1,1,4,4,1,1,1}, {11,1,1,1,1,1,1,1}, {1,1,1,1,-1,-1,-1,-1}, {1,2,3,4,5,6,7,8}, {1,-1,1,-1,1,-1,1,-1} };
	vector<double> b3 = { 0,0,0,0,20,34,-51,-6 };
	elimAndPrint(A3, b3);
	cout << endl;
	pathCalculator();
}
