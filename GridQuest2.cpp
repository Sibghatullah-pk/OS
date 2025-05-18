#include <iostream>
#include <pthread.h>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

const int MAX_PLAYERS = 10;
int n;
int board[25][25];
int numPlayers;

struct Player {
    int x, y, score;
    queue<string> msgQueue;
    bool active;
};

Player players[MAX_PLAYERS];
pthread_t playerThreads[MAX_PLAYERS];

void generateBoardSize(int roll ) {
    srand(time(0));
    int randNum = rand() % 90 + 10;
    int lastDigit = roll % 10;
    if (lastDigit == 0) lastDigit = 1;
    int temp = randNum * lastDigit;
    n = roll / temp;
    n %= 25;
    if (n < 10) n += 15;
}

void initBoard() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = (rand() % 10 < 2) ? 1 : 0;
}

void initPlayers() {
    cout << "Enter number of players (1-" << MAX_PLAYERS << "): ";
    cin >> numPlayers;
    if (numPlayers > MAX_PLAYERS) numPlayers = MAX_PLAYERS;

    for (int i = 0; i < numPlayers; i++) {
        int x, y;
        do {
            x = rand() % n;
            y = rand() % n;
        } while (board[x][y] == 1);
        players[i] = {x, y, 0, queue<string>(), true};
    }
}

void printBoard() {
    system("clear");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool printed = false;
            for (int p = 0; p < numPlayers; p++) {
                if (players[p].x == i && players[p].y == j && players[p].active) {
                    cout << "P" << p + 1 << " ";
                    printed = true;
                    break;
                }
            }
            if (!printed) cout << (board[i][j] == 1 ? "I " : ". ");
        }
        cout << endl;
    }
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << i + 1 << ": Score=" << players[i].score
             << " Position=(" << players[i].x << "," << players[i].y << ")\n";
    }
    cout << "Format: player_id (1 to " << numPlayers << ") + movement key (WASD) or Q to quit\n";
}

void* playerThread(void* arg) {
    int id = *(int*)arg;
    while (players[id].active) {
        if (!players[id].msgQueue.empty()) {
            string msg = players[id].msgQueue.front();
            players[id].msgQueue.pop();

            if (msg == "QUIT") {
                players[id].active = false;
                break;
            }

            int dx = 0, dy = 0;
            if (msg == "W") dx = -1;
            else if (msg == "S") dx = 1;
            else if (msg == "A") dy = -1;
            else if (msg == "D") dy = 1;

            int newX = players[id].x + dx;
            int newY = players[id].y + dy;

            if (newX >= 0 && newX < n && newY >= 0 && newY < n) {
                bool occupied = false;
                for (int j = 0; j < numPlayers; j++) {
                    if (j != id && players[j].x == newX && players[j].y == newY && players[j].active)
                        occupied = true;
                }
                if (!occupied) {
                    players[id].x = newX;
                    players[id].y = newY;
                    if (board[newX][newY] == 1) {
                        board[newX][newY] = 0;
                        players[id].score += 10;
                    }
                }
            }
        }
        usleep(100000); // 0.1 sec
    }
    return nullptr;
}

int main() {
    generateBoardSize(230896);
    initBoard();
    initPlayers();

    int ids[MAX_PLAYERS];
    for (int i = 0; i < numPlayers; i++) {
        ids[i] = i;
        pthread_create(&playerThreads[i], nullptr, playerThread, &ids[i]);
    }

    while (true) {
        printBoard();
        int pid;
        char cmd;
        cout << "Enter: ";
        cin >> pid >> cmd;
        if (pid < 1 || pid > numPlayers) continue;
        pid -= 1;

        if (!players[pid].active) continue;

        if (cmd == 'q' || cmd == 'Q')
            players[pid].msgQueue.push("QUIT");
        else if (cmd == 'w' || cmd == 'W')
            players[pid].msgQueue.push("W");
        else if (cmd == 'a' || cmd == 'A')
            players[pid].msgQueue.push("A");
        else if (cmd == 's' || cmd == 'S')
            players[pid].msgQueue.push("S");
        else if (cmd == 'd' || cmd == 'D')
            players[pid].msgQueue.push("D");

        bool allQuit = true;
        for (int i = 0; i < numPlayers; i++) {
            if (players[i].active) allQuit = false;
        }
        if (allQuit) break;
    }

    for (int i = 0; i < numPlayers; i++)
        pthread_join(playerThreads[i], nullptr);

    cout << "Game Over!\n";
    return 0;
}

