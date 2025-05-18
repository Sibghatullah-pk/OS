#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

int n;
int board[25][25];
int numPlayers;

struct Player {
    int x, y, score;
};

Player players[10];

void generateBoardSize() {
    srand(time(0));
    int temp = rand() % 99 + 1;
    n = rand() % temp + 1;
    n *= 6;
    if (n == 0) n = 1;
    n = 230896 / n;
    n %= 25;
    if (n < 10) n += 15;
    else cout << "matrix number " << n << endl;
}

void initBoard() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = (rand() % 10 < 2) ? 1 : 0;
}

void initPlayers() {
    cout << "How many players? ";
    cin >> numPlayers;
    for (int i = 0; i < numPlayers; i++) {
        int x, y;
        do {
            x = rand() % n;
            y = rand() % n;
        } while (board[x][y] == 1);
        players[i] = {x, y, 0};
        cout << "Player " << i + 1 << " starts at (" << x << ", " << y << ")\n";
    }
}

void printBoard() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool isPlayerHere = false;
            for (int k = 0; k < numPlayers; k++) {
                if (players[k].x == i && players[k].y == j) {
                    cout << "P" << k + 1 << " ";
                    isPlayerHere = true;
                    break;
                }
            }
            if (!isPlayerHere) {
                if (board[i][j] == 1) cout << "I ";
                else cout << ". ";
            }
        }
        cout << endl;
    }
    for (int k = 0; k < numPlayers; k++) {
        cout << "Player " << k + 1 << " Score: " << players[k].score
             << " (Position: " << players[k].x << "," << players[k].y << ")\n";
    }
}

int main() {
    generateBoardSize();
    initBoard();
    initPlayers();

    bool gameRunning = true;
    while (gameRunning) {
        system("clear");
        printBoard();
        for (int i = 0; i < numPlayers; i++) {
            char move;
            cout << "Player " << i + 1 << " (WASD to move, Q to quit): ";
            cin >> move;
            int newX = players[i].x, newY = players[i].y;
            if (move == 'w' || move == 'W') newX--;
            else if (move == 's' || move == 'S') newX++;
            else if (move == 'a' || move == 'A') newY--;
            else if (move == 'd' || move == 'D') newY++;
            else if (move == 'q' || move == 'Q') {
                gameRunning = false;
                break;
            }
            if (newX >= 0 && newX < n && newY >= 0 && newY < n) {
                bool canMove = true;
                for (int j = 0; j < numPlayers; j++) {
                    if (i != j && players[j].x == newX && players[j].y == newY) {
                        canMove = false;
                        break;
                    }
                }
                if (canMove) {
                    players[i].x = newX;
                    players[i].y = newY;
                    if (board[newX][newY] == 1) {
                        board[newX][newY] = 0;
                        players[i].score += 10;
                    }
                }
            }
        }
        sleep(1);
    }

    cout << "Game Over!\n";
    return 0;
}
