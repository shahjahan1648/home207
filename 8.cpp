#include <iostream>
using namespace std;

const int MAX = 20;
int board[MAX][MAX];

// Check if it's safe to place a queen
bool isSafe(int row, int col, int n) {

    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function
bool solveNQueens(int row, int n) {

    // Base case: all queens placed
    if (row == n)
        return true;

    for (int col = 0; col < n; col++) {

        if (isSafe(row, col, n)) {

            board[row][col] = 1; // place queen

            if (solveNQueens(row + 1, n))
                return true;

            board[row][col] = 0; // backtrack
        }
    }

    return false;
}

// Print solution
void printBoard(int n) {
    cout << "\nSolution:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    // Initialize board
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    if (solveNQueens(0, n))
        printBoard(n);
    else
        cout << "No solution exists\n";

    return 0;
}