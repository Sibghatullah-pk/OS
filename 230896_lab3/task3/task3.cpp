#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int num_processes = 5;
    pid_t pid;

    cout << "Parent: Creating child processes...\n";

    for (int i = 0; i < num_processes; i++) {
        pid = fork();

        if (pid == 0) {  
            // Child process
            sleep(2 + i);  // Simulate different work times
            exit(i % 2);  // Exit with status 0 or 1
        } else if (pid < 0) {  
            // Fork failed
            cerr << "Error: Fork failed!\n";
            exit(1);
        }
    }

    // Parent process continues working while checking for child processes
    int status;
    pid_t child_pid;
    
    cout << "Parent: Working while waiting for children...\n";

    while (num_processes > 0) {
        sleep(1);  // Simulate parent working
        cout << "Parent: Still working...\n";

        // Check if any child has finished
        while ((child_pid = waitpid(-1, &status, WNOHANG)) > 0) {
            cout << "Parent: A child exited with status " << WEXITSTATUS(status) << "\n";
            num_processes--;
        }
    }

    cout << "Parent: All child processes finished. Exiting.\n";
    return 0;
}

