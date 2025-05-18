#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int main() {
    int pipefd[2]; // pipefd[0] for reading, pipefd[1] for writing
    if (pipe(pipefd) == -1) {
        cout << "Pipe creation failed!" << endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close write end
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        cout << "Child received: " << buffer << endl;
        close(pipefd[0]);
        exit(0);
    } else if (pid > 0) {
        // Parent process
        close(pipefd[0]); // Close read end
        string message = "Hello, Child!";
        write(pipefd[1], message.c_str(), message.length() + 1);
        close(pipefd[1]);
        wait(NULL);
    } else {
        cout << "Fork failed!" << endl;
        return 1;
    }
    return 0;
}
