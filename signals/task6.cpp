#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "A suicidal program" << endl;

    // Raise SIGKILL, which immediately terminates the process
    raise(SIGKILL);

    // This line will never be executed
    cout << "Terminating..." << endl;

    return 0;
}

