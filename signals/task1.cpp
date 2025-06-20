#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main() {
    // Ignoring signals
    signal(SIGQUIT, SIG_IGN); // Ignore Ctrl + \
    signal(SIGTSTP, SIG_IGN); // Ignore Ctrl + Z
    signal(SIGINT, SIG_IGN);  // Ignore Ctrl + C

    for (int i = 0;; i++) {
        cout << i << " My pid is: " << getpid() << endl;
        cout << "You can't close me using conventional commands" << endl;
        sleep(2);
    }

    return 0;
}

