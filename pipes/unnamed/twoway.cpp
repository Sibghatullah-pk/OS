#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int main() {
    int parent_to_child[2]; // Pipe for parent to child
    int child_to_parent[2]; // Pipe for child to parent

    // Create both pipes
    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        cerr << "Pipe creation failed!" << endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(parent_to_child[1]); // Close write end of parent-to-child pipe
        close(child_to_parent[0]); // Close read end of child-to-parent pipe

        char buffer[100];
        bool running = true;

        while (running) {
            // Read from parent
            int bytes_read = read(parent_to_child[0], buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                cout << "Child received: " << buffer;

                // Check for "bye"
                if (strcmp(buffer, "bye\n") == 0) {
                    running = false;
                    continue;
                }

                // Write to parent
                string message;
                cout << "Child: ";
                getline(cin, message);
                message += "\n";
                write(child_to_parent[1], message.c_str(), message.length());

                if (message == "bye\n") {
                    running = false;
                }
            }
            sleep(1); // To avoid race conditions
        }

        close(parent_to_child[0]);
        close(child_to_parent[1]);
        exit(0);
    } else {
        // Parent process
        close(parent_to_child[0]); // Close read end of parent-to-child pipe
        close(child_to_parent[1]); // Close write end of child-to-parent pipe

        char buffer[100];
        bool running = true;

        while (running) {
            // Write to child
            string message;
            cout << "Parent: ";
            getline(cin, message);
            message += "\n";
            write(parent_to_child[1], message.c_str(), message.length());

            if (message == "bye\n") {
                running = false;
                continue;
            }

            // Read from child
            int bytes_read = read(child_to_parent[0], buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                cout << "Parent received: " << buffer;

                if (strcmp(buffer, "bye\n") == 0) {
                    running = false;
                }
            }
            sleep(1); // To avoid race conditions
        }

        close(parent_to_child[1]);
        close(child_to_parent[0]);
        wait(nullptr);
    }

    return 0;
}
