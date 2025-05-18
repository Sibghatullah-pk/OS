#include <iostream>
#include <pthread.h>
using namespace std;

const int ROWS_A = 3, COLS_A = 4, ROWS_B = 4, COLS_B = 3;
int A[ROWS_A][COLS_A], B[ROWS_B][COLS_B], C[ROWS_A][COLS_B];
pthread_mutex_t mtx;
pthread_t threads[ROWS_A];

void* multiplyRow(void* arg) {
    int row = *(int*)arg;
    for (int j = 0; j < COLS_B; j++) {
        int sum = 0;
        for (int k = 0; k < COLS_A; k++) {
            sum += A[row][k] * B[k][j];
        }
        pthread_mutex_lock(&mtx);
        C[row][j] = sum;
        pthread_mutex_unlock(&mtx);
    }
    return nullptr;
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

    int rowIndices[ROWS_A];
    for (int i = 0; i < ROWS_A; i++) {
        rowIndices[i] = i;
        if (pthread_create(&threads[i], NULL, multiplyRow, &rowIndices[i]) != 0) {
            cout << "Failed to create thread for row " << i + 1 << endl;
            return 1;
        }
    }

    for (int i = 0; i < ROWS_A; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            cout << "Failed to join thread for row " << i + 1 << endl;
            return 1;
        }
    }

    cout << "Result Matrix C (" << ROWS_A << "x" << COLS_B << "):\n";
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    pthread_mutex_destroy(&mtx);
    return 0;
}
