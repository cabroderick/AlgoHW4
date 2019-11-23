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
// B: The system's right-hand side values
// n: The dimensions of array A
// Returns the solved matrix
using namespace std;
#include <malloc.h>
#include <vector>
#include <iostream>
vector< vector<int> > Elimination (vector<vector<int> > A, vector<int> b) {
	int n = A.size(); // The dimensions of the matrix
	for (int i = 0; i < A.size(); i++) {
		A.at(i).push_back(b.at(i));
	}
	for (int i = 0; i < n - 1; i++) {
		int pivotrow = i;
		for (int j = i + 1; j < n; j++) {
			if (A[j][i] > A[pivotrow][i]) pivotrow = j;
		}
		for (int k = i; k < n + 1; k++) {
			int temp1 = A[i][k]; // ERROR OCCURS HERE
			int temp2 = A[pivotrow][k];
			A[i][k] = temp2;
			A[pivotrow][k] = temp1;
		}
		for (int j = i + 1; j < n; j++) {
			int temp = A[j][i] / A[i][i];
			for (int k = i; k < n + 1; k++) {
				A[j][k] = A[j][k] - A[i][k] * temp;
			}
		}
	}
	return A;
}

int main() {
	vector<vector<int>> A = { {1, 1, -1}, {0, 1, 3}, {-1, 0, 2} };	
	vector<int> b = { 9, 3, 2 };
	vector<vector<int>> B = Elimination(A, b);
	for (int i = 0; i < A.size(); i++) {
		for (int k = 0; k < A[i].size(); k++) {
			cout << B[i][k] << " "; // Prints the matrix
		}
		cout << endl;
	}
}
