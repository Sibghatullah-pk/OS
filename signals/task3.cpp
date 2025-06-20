#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        cout << "Child process not created" << endl;
    } 
    else if (pid > 0) {
        // Parent process
        cout << "I am the parent with pid " << getpid()
             << " and child pid is " << pid << endl;
        wait(NULL); // Wait for child to terminate
    } 
    else {
        // Child process
        cout << "I am the child with pid " << getpid()
             << " and my parent pid is " << getppid() << endl;

        // Kill parent
        kill(getppid(), SIGKILL);

        // After killing, parent should be reaped by init/systemd
        sleep(1); // Give time for re-parenting to occur
        cout << "My new parent pid is " << getppid() << endl;
    }

    return 0;
}

