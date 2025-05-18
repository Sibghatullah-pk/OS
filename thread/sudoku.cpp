#include <iostream>
using namespace std;

// 9x9 Sudoku board (0 means empty cell)
int board[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// Function to print the Sudoku board
void printBoard() {
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "---------------------" << endl; // Separator for 3x3 boxes
        }
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << "| "; // Separator for 3x3 boxes
            }
            if (board[row][col] == 0) {
                cout << ". ";
            } else {
                cout << board[row][col] << " ";
            }
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in the given position
bool isSafe(int row, int col, int num) {
    // Check row
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < 9; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to validate the entire board
bool isValidSudoku() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] != 0) {
                int num = board[row][col];
                board[row][col] = 0; // Temporarily set to 0 to check
                if (!isSafe(row, col, num)) {
                    board[row][col] = num; // Restore the number
                    return false;
                }
                board[row][col] = num; // Restore the number
            }
        }
    }
    return true;
}

int main() {
    cout << "Welcome to Sudoku Game!" << endl;
    cout << "Fill the empty cells (marked as '.') with numbers 1-9." << endl;
    cout << "Enter row (1-9), column (1-9), and number (1-9). To exit, enter 0 for row." << endl;
    cout << "Initial Sudoku Board:" << endl;
    printBoard();

    while (true) {
        int row, col, num;
        cout << "\nEnter row (1-9, or 0 to exit): ";
        cin >> row;
        if (row == 0) break; // Exit condition
        cout << "Enter column (1-9): ";
        cin >> col;
        cout << "Enter number (1-9): ";
        cin >> num;

        // Adjust for 0-based indexing
        row--;
        col--;

        // Input validation
        if (row < 0 || row >= 9 || col < 0 || col >= 9 || num < 1 || num > 9) {
            cout << "Invalid input! Try again." << endl;
            continue;
        }

        // Check if the cell is empty and the number can be placed
        if (board[row][col] != 0) {
            cout << "Cell already filled! Try another cell." << endl;
            continue;
        }

        if (isSafe(row, col, num)) {
            board[row][col] = num;
            cout << "Updated Board:" << endl;
            printBoard();
        } else {
            cout << "Number cannot be placed here! Try again." << endl;
        }

        // Check if the board is completely filled and valid
        bool filled = true;
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == 0) {
                    filled = false;
                    break;
                }
            }
        }
        if (filled && isValidSudoku()) {
            cout << "Congratulations! You've solved the Sudoku!" << endl;
            break;
        }
    }

    cout << "Final Board:" << endl;
    printBoard();
    return 0;
}
