#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void myhandler(int signum) {
    cout << "Processing a SIGINT signal: " << signum << endl;
}

int main() {
    // Register handler for SIGINT (Ctrl+C)
    signal(SIGINT, myhandler);

    cout << "Beginning execution — touch CTRL+C to continue program" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "Value of i is " << i << endl;
        pause(); // Waits until a signal is received
    }

    return 0;
}

