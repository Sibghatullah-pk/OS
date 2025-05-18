#include <iostream>
#include <thread>
#include <cmath>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

// Matrix dimensions
const int ROWS_W = 3, COLS_W = 4, ROWS_X = 4, COLS_X = 1;
double W[ROWS_W][COLS_W] = {
    {0.2, -0.5, 0.1, 2.0},
    {1.5, 1.3, 2.1, 0.0},
    {0, 0.25, 0.2, -0.3}
};
double X[ROWS_X][COLS_X] = {
    {56},
    {231},
    {24},
    {2}
};
double b[ROWS_W][COLS_X] = {
    {2},
    {2},
    {2}
};
double Z[ROWS_W][COLS_X], A[ROWS_W][COLS_X];

// P1: Matrix multiplication (W * X)
void multiplyRow(int row, double result[ROWS_W][COLS_X]) {
    for (int j = 0; j < COLS_X; j++) {
        result[row][j] = 0;
        for (int k = 0; k < COLS_W; k++) {
            result[row][j] += W[row][k] * X[k][j];
        }
    }
}

// P2: Matrix addition (Z + b)
void addBias(int row, double input[ROWS_W][COLS_X], double result[ROWS_W][COLS_X]) {
    for (int j = 0; j < COLS_X; j++) {
        result[row][j] = input[row][j] + b[row][j];
    }
}

// P3: Sigmoid function
void applySigmoid(int row, double input[ROWS_W][COLS_X], double result[ROWS_W][COLS_X]) {
    for (int j = 0; j < COLS_X; j++) {
        result[row][j] = 1.0 / (1.0 + exp(-input[row][j]));
    }
}

int main() {
    int pipe1[2], pipe2[2]; // Pipes for communication
    pipe(pipe1);
    pipe(pipe2);

    pid_t p1 = fork();
    if (p1 == 0) {
        // Process P1: Matrix multiplication
        close(pipe1[0]); // Close reading end
        thread threads[ROWS_W];
        for (int i = 0; i < ROWS_W; i++) {
            threads[i] = thread(multiplyRow, i, Z);
        }
        for (int i = 0; i < ROWS_W; i++) {
            threads[i].join();
        }
        write(pipe1[1], Z, sizeof(Z));
        close(pipe1[1]);
        exit(0);
    }

    pid_t p2 = fork();
    if (p2 == 0) {
        // Process P2: Matrix addition
        close(pipe1[1]); // Close writing end of pipe1
        close(pipe2[0]); // Close reading end of pipe2
        read(pipe1[0], Z, sizeof(Z));
        close(pipe1[0]);

        thread threads[ROWS_W];
        for (int i = 0; i < ROWS_W; i++) {
            threads[i] = thread(addBias, i, Z, Z);
        }
        for (int i = 0; i < ROWS_W; i++) {
            threads[i].join();
        }
        write(pipe2[1], Z, sizeof(Z));
        close(pipe2[1]);
        exit(0);
    }

    // Process P3 (Parent): Sigmoid
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);
    read(pipe2[0], Z, sizeof(Z));
    close(pipe2[0]);

    thread threads[ROWS_W];
    for (int i = 0; i < ROWS_W; i++) {
        threads[i] = thread(applySigmoid, i, Z, A);
    }
    for (int i = 0; i < ROWS_W; i++) {
        threads[i].join();
    }

    // Output
    cout << "Final Activation Matrix A:\n";
    for (int i = 0; i < ROWS_W; i++) {
        for (int j = 0; j < COLS_X; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    wait(NULL);
    wait(NULL);

    return 0;
}
