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
vector< vector<double> > Elimination (vector<vector<double> > A, vector<double> b) {
	double n = A.size(); // The rows of the matrix
	for (int i = 0; i < n; i++) {
		A.at(i).push_back(b.at(i));
	}
	for (int i = 0; i < n - 1; i++) {
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
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n + 1; k++) {
					cout << A[j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	return A;
}

int main() {
	vector<vector<double>> A = { {1, 1, -1}, {0, 1, 3}, {-1, 0, 2} };	
	vector<double> b = { 9, 3, 2 };
	vector<vector<double>> A2 = { {1, 1, 1}, {1, 1, 2}, {2, 2, 3} };
	vector<double> b2 = { 6, 9, 15 };
	vector<vector<double>> A3 = { {1,1,1,1,1,1,1,1}, {1,2,1,1,1,1,2,1}, {1,1,3,1,1,3,1,1}, {1,1,1,4,4,1,1,1}, {11,1,1,1,1,1,1,1}, {1,1,1,1,-1,-1,-1,-1}, {1,2,3,4,5,6,7,8}, {1,-1,1,-1,1,-1,1,-1} };
	vector<double> b3 = { 0,0,0,0,20,34,-51,-6 };
	vector<vector<double>> B = Elimination(A3, b3);
}
