#include <iostream>
#include <thread>
using namespace std;

const int ROWS_A = 2, COLS_A = 3, ROWS_B = 3, COLS_B = 2;
int A[ROWS_A][COLS_A], B[ROWS_B][COLS_B], C[ROWS_A][COLS_B];

void multiplyRow(int row) {
    for (int j = 0; j < COLS_B; j++) {
        C[row][j] = 0;
        for (int k = 0; k < COLS_A; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
}

int main() {
    cout << "Enter matrix A (" << ROWS_A << "x" << COLS_A << "):\n";
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter matrix B (" << ROWS_B << "x" << COLS_B << "):\n";
    for (int i = 0; i < ROWS_B; i++) {
        for (int j = 0; j < COLS_B; j++) {
            cin >> B[i][j];
        }
    }

    thread threads[ROWS_A]; // simple array of threads (not vector)

    for (int i = 0; i < ROWS_A; i++) {
        threads[i] = thread(multiplyRow, i);
    }

    for (int i = 0; i < ROWS_A; i++) {
        threads[i].join();
    }

    cout << "Result Matrix C (" << ROWS_A << "x" << COLS_B << "):\n";
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
