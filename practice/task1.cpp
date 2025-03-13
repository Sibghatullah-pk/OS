#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

pid_t root_pid;

int main() {
cout<<"pid before any creation "<<getpid()<< endl;;
    root_pid = getpid();

    if (fork() != 0) {
        fork();
    } else {
        if (fork() || !fork()) {
            if (fork() == 0) {
                pid_t pid = fork();

                if (pid == 0) {
                    cout << "In C7 (PID: " << getpid() << "), the PID of P is: " << root_pid << endl;
                    exit(0);
                }
            }
        }
    }
    return 0;
}
