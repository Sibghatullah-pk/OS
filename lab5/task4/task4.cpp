#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int main() {
    int pipefd1[2], pipefd2[2];
    char msg[100];

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        cerr << "Pipe problem!\n";
        return 1;
    }

    pid_t p_id = fork();
    if (p_id == -1) {
        cerr << "Fork failed!\n";
        return 1;
    }

    if (p_id == 0) {
        close(pipefd1[1]);
        close(pipefd2[0]);

        while (true) {
            int bytes = read(pipefd1[0], msg, sizeof(msg));
            msg[bytes] = '\0';
            cout << "Child got: " << msg << endl;
            if (strcmp(msg, "bye") == 0) break;

            cout << "Child: ";
            cin >> msg;
            write(pipefd2[1], msg, strlen(msg) + 1);
            if (strcmp(msg, "bye") == 0) break;
        }

        close(pipefd1[0]);
        close(pipefd2[1]);
        exit(0);
    } else {
        close(pipefd1[0]);
        close(pipefd2[1]);

        while (true) {
            cout << "Parent: ";
            cin >> msg;
            write(pipefd1[1], msg, strlen(msg) + 1);

            if (strcmp(msg, "bye") == 0) break;

            int bytes = read(pipefd2[0], msg, sizeof(msg));
            msg[bytes] = '\0';
            cout << "Parent got: " << msg << endl;
            if (strcmp(msg, "bye") == 0) break;
        }

        close(pipefd1[1]);
        close(pipefd2[0]);
        waitpid(p_id, nullptr, 0);
    }

    return 0;
}
