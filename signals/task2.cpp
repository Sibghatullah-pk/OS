#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void myhandler(int signal_number) {
    // Resetting the signal handler inside the handler (optional for some systems)
    signal(SIGINT, myhandler);
    cout << "Inside my custom handler. Received signal: " << signal_number << endl;
}

int main() {
    signal(SIGINT, myhandler); // Adding custom handler for Ctrl + C

    for (int i = 0;; i++) {
        cout << i << endl;
        sleep(2); // Slow down to observe behavior
    }

    return 0;
}

