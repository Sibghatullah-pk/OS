#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int cpid; // Global so handler can access

void handler(int signum) {
    cout << "Signal received: " << signum << endl;

    if (signum == SIGUSR1) {
        cout << "Received SIGUSR1 from child." << endl;
    } else if (signum == SIGCHLD) {
        while (kill(cpid, 0) == 0) {
            cout << "Waiting for child..." << endl;
            sleep(1);
        }
        cout << "Child terminated. Now parent is terminating." << endl;
        exit(0);
    }
}

int main() {
    signal(SIGUSR1, handler);
    signal(SIGCHLD, handler);

    cpid = fork();

    switch (cpid) {
        case -1:
            cout << "Error creating child process" << endl;
            break;

        case 0: {
            // Child process
            int ppid = getppid();
            sleep(1); // Give parent time to set up signal handlers
            kill(ppid, SIGUSR1); // Send signal to parent
            sleep(2); // Simulate some work
            exit(0);
            break;
        }

        default:
            // Parent process
            while (true) {
                pause(); // Wait for signals
            }
    }

    return 0;
}

