#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
using namespace std;

int x = 0;

void handler(int signum) {
    if (x == 0) {
        cout << "\n(hint): simple add bro" << endl;
    }
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        sleep(1);  // Wait 5 seconds before sending signal
        kill(getppid(), SIGUSR1);  // Send signal to parent
        return 0;
    } else {
        // Parent process
        struct sigaction sa;
        sa.sa_handler = handler;
        sa.sa_flags = SA_RESTART;  // Restart interrupted system calls (like cin)
        sigaction(SIGUSR1, &sa, NULL);

        cout << "What is the result of 3 + 5? ";  // Matches hint
        cin >> x;

        if (x == 8) {
            cout << "Correct!" << endl;
        } else {
            cout << "Failed." << endl;
        }
    }

    return 0;
}

