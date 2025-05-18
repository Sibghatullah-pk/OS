

#include <iostream>
#include <pthread.h>
using namespace std;
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
pthread_mutex_t mutex;
bool isValid = true;
void printBoard() {
for (int row = 0; row < 9; row++) {
if (row % 3 == 0 && row != 0) {
cout << "---------------------" << endl;
}
for (int col = 0; col < 9; col++) {
if (col % 3 == 0 && col != 0) {
cout << "| ";
}
if (board[row][col] == 0) {
cout << ". ";
}
else {
cout << board[row][col] << " ";
}
}
cout << endl;
}
}
void* checkRow(void* arg) {
int row = *(int*)arg;
bool seen[10] = {false};
for (int col = 0; col < 9; col++) {
int num = board[row][col];
if (num == 0) continue;
if (num < 1 || num > 9 || seen[num]) {
pthread_mutex_lock(&mutex);
isValid = false;
cout << "Invalid number maherbani kr " << row + 1 << ": " << num << endl;
pthread_mutex_unlock(&mutex);
break;
}
seen[num] = true;
}
return nullptr;
}
void* checkColumn(void* arg) {
int col = *(int*)arg;
bool seen[10] = {false};
for (int row = 0; row < 9; row++) {
int num = board[row][col];
if (num == 0)
 continue;
if (num < 1 || num > 9 || seen[num]) {
pthread_mutex_lock(&mutex);
isValid = false;
cout << "Invalid number in column " << col + 1 << ": " << num << endl;
pthread_mutex_unlock(&mutex);
break;
}
seen[num] = true;
}
return nullptr;
}
void* checkPrimaryDiagonal(void* arg) {
bool seen[10] = {false};
for (int i = 0; i < 9; i++) {
int num = board[i][i];
if (num == 0) continue;
if (num < 1 || num > 9 || seen[num]) {
pthread_mutex_lock(&mutex);
isValid = false;
cout << "Invalid number in (" << i + 1 << "," << i + 1 << "): " << num << endl;
pthread_mutex_unlock(&mutex);
break;
}
seen[num] = true;
}
return nullptr;
}
bool valid() {
pthread_t rowThreads[9], colThreads[9], diagThread;
int rowIndices[9], colIndices[9];
isValid = true;
for (int i = 0; i < 9; i++) {
rowIndices[i] = i;
if (pthread_create(&rowThreads[i], NULL, checkRow, &rowIndices[i]) != 0) {
cout << "Failed to create thread " << i + 1 << endl;
return false;
}
}
for (int i = 0; i < 9; i++) {
colIndices[i] = i;
if (pthread_create(&colThreads[i], NULL, checkColumn, &colIndices[i]) != 0) {
cout << "Failed to create thread for column " << i + 1 << endl;
return false;
}
}
if (pthread_create(&diagThread, NULL, checkPrimaryDiagonal, NULL) != 0) {
cout << "Failed to create thread for primary diagonal" << endl;
return false;
}
for (int i = 0; i < 9; i++) {
pthread_join(rowThreads[i], NULL);
}
for (int i = 0; i < 9; i++) {
pthread_join(colThreads[i], NULL);
}
pthread_join(diagThread, NULL);
return isValid;
}
int main() {
if (pthread_mutex_init(&mutex, NULL) != 0) {
cout << "Mutex initialization failed" << endl;
return 1;
}
cout << "hii! maherbani :) itna easy code khlttttttttttt." << endl;
cout << "Fill the empty cells (marked as '.') with numbers 1-9." << endl;
cout << "Enter row (1-9), column (1-9), and nber (1-9). To exit, enter 0 for row." << endl;
printBoard();
while (true) {
int row, col, num;
cout << "\nEnter row (1-9, or 0 to exit): ";
cin >> row;
if (row == 0) break;
cout << "Enter column (1-9): ";
cin >> col;
cout << "Enter number (1-9): ";
cin >> num;
row--; col--;
if (row < 0 || row >= 9 || col < 0 || col >= 9 || num < 1 || num > 9) {
cout << "Invalid input! 0 dabba ni ona tra sa." << endl;
continue;
}
if (board[row][col] != 0) {
cout << "Cell already filled! kha tha nah." << endl;
continue;
}
board[row][col] = num;
if (valid()) {
cout << "Updated Board:sukr" << endl;
printBoard();
}
else {
cout << "Number cannot be placed here! itny bzty kfy" << endl;
board[row][col] = 0;
}
bool filled = true;
for (int r = 0; r < 9; r++) {
for (int c = 0; c < 9; c++) {
if (board[r][c] == 0) {
filled = false;
break;
}
}
}
if (filled && valid()) {
cout << "Congratulations!jis nah bnanya os ko " << endl;
break;
}
}
cout << "Final Board:" << endl;
printBoard();
pthread_mutex_destroy(&mutex);
return 0;
}
