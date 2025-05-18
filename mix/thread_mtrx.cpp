#include <iostream>
#include <thread>
#include <vector>
using namespace std;

const int ROWS = 2, COLS = 2;
int A[ROWS][COLS] = {{1, 2}, {3, 4}};
int B[ROWS][COLS] = {{5, 6}, {7, 8}};
int C[ROWS][COLS];

void multiplyRow(int row) {
    for (int j = 0; j < COLS; j++) {
        C[row][j] = 0;
        for (int k = 0; k < COLS; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < ROWS; i++) {
        threads.emplace_back(multiplyRow, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "Result Matrix C:\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
