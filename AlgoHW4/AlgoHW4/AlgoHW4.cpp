// Collin Broderick, Praise Eteng, Siddhant Banerjee

/* Questions
1. ForwardElimination fails to provide a solution to the given system because after it iterates through the second row of the matrix, the pivot position's
value becomes 0. When the algorithm tries to iterate through the third row, it will divide its elements by the pivot position value of 0, which will result
in a divide by 0 error and the algorithm will terminate.
BetterForwardElimination remedies this by swapping the pivot row with the row with the greatest value for a pivot position, preventing divide by 0 errors
in the case where the system has a solution.
2.
*/

int main() {

}