#include <bits/stdc++.h>
#include <sys/wait.h>
int global = 0;  // Global variable

int main() {
    int status;
    pid_t child_pid;
    int local = 0;  // Local variable

    // Create a new process using fork
    child_pid = fork();

    if (child_pid >= 0) {  // Fork succeeded
        if (child_pid == 0) {  // Child process
            std::cout << "Child process!\n";
            local++;
            global++;
            std::cout << "Child PID = " << getpid() << ", Parent PID = " << getppid() << "\n";
            std::cout << "Child's local = " << local << ", Child's global = " << global << "\n";
            exit(0);  // Child exits after printing
        } else {  // Parent process
            std::cout << "Parent process!\n";
            std::cout << "Parent PID = " << getpid() << ", Child PID = " << child_pid << "\n";
            wait(&status);  // Wait for child to finish
            std::cout << "\nParent's local = " << local << ", Parent's global = " << global << "\n";
            std::cout << "Parent says bye!\n";
            exit(0);  // Parent exits
        }
    } else {
        std::cerr << "Fork failed: " << std::endl;  // Use cerr for errors
        exit(1);  // Exit with error code
    }

    return 0;  // Return for C++ main (though exit() already terminates)
}
