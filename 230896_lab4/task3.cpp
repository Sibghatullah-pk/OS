#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main() {
    // Open a file in the parent process
    int file = open("testfile.txt", O_CREAT | O_RDWR);
    if (file == -1) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    // Write something to the file to check later
    write(file, "Hello from parent!", 18);

    // Fork to create a child process
    pid_t pid = fork();

    if (pid == -1) {
        cerr << "Failed to fork child" << endl;
        close(file);
        return 1;
    }

    if (pid == 0) {
        // Child process

        // In the child, try to access the file opened by the parent
        cout << "Child process is trying to access the file..." << endl;

        // Print the file descriptor number (which should be inherited)
        cout << "File descriptor in child process: " << file << endl;

        // Execute another program (e.g., 'cat' to print the contents of the file)
        execlp("cat", "cat", "testfile.txt", (char*)NULL);

        // If execlp fails
        cerr << "Failed to execute 'cat' program" << endl;
        return 1;
    } else {
        // Parent process
        // Wait for the child process to complete
        wait(NULL);

        // Print something to indicate parent has finished
        cout << "Parent process has completed" << endl;

        // Close the file in the parent
        close(file);
    }

    return 0;
}
